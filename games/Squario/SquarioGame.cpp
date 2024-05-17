#include <Arduboy2.h>
#include "DefinesImagesAndSounds.h"
#include "SquarioGame.h"

uint8_t Sprite::Width( )          { return pgm_read_byte( SpriteData + SpriteWidth ); }
uint8_t Sprite::Height( )         { return pgm_read_byte( SpriteData + SpriteHeight ); }
uint8_t Sprite::Masks( )          { return pgm_read_byte( SpriteData + SpriteMasks ); }
uint8_t Sprite::MaxFrame( )       { return pgm_read_byte( SpriteData + SpriteMaxFrame ); }
uint8_t Sprite::CyclesPerFrame( ) { return pgm_read_byte( SpriteData + SpriteCyclesPerFrame ); }
uint8_t    Sprite::Flags( )          { return pgm_read_byte( SpriteData + SpriteFlags ); }
const uint8_t * Sprite::FramePointer ( ) {
  int16_t FrameSize = Height() * Width() / 8;
  return SpriteData + SpriteImageData + ( FrameSize * ( currentFrame / CyclesPerFrame() ) );
}
const uint8_t * Sprite::MaskPointer ( ) {
  int16_t FrameSize = Height() * Width() / 8;
  return SpriteData + SpriteImageData + ( FrameSize * MaxFrame() ) + ( FrameSize * ( currentFrame / CyclesPerFrame() ) );
}
void Sprite::LoadSprite( const uint8_t * DataPointer, int16_t tX, int16_t tY ) {
  SpriteData = DataPointer;
  x = tX; y = tY;
  vx = 0; vy = 0;
  Mirrored = false;
  currentFrame = 0;
}
void Sprite::ClearSprite( ) {
  SpriteData = NULL;
  x = -1;
  y = -1;
  vx = 0;
  vy = 0;
  currentFrame = 0;
  Mirrored = false;
}
bool Sprite::IsIn ( int16_t tX, int16_t tY ) {
  if ( tX >= x &&
       tX <= RightX() &&
       tY >= y &&
       tY <= BottomY() ) return true;
  return false;
}
bool Sprite::IsInTopHalf ( int16_t tX, int16_t tY ) {
  if ( tX >= x &&
       tX <= RightX() &&
       tY >= y &&
       tY <= (y+(Height()/2)) ) return true;
  return false;
}
bool Sprite::GetPixelAbsolute( int16_t tX, int16_t tY ) {
  int16_t RelativeX = tX - x;
  int16_t RelativeY = tY - y;
  if ( RelativeX < 0 || RelativeY < 0 || RelativeX > Width() || RelativeY > Height() ) return false;
  uint8_t row = RelativeY / 8;
  uint8_t offset = RelativeY % 8;
  uint8_t selection = pgm_read_byte( MaskPointer() + ( row * Width() ) + RelativeX );
  return ( selection & ( 1 << offset ) );
}
uint8_t Sprite::Collide( int16_t tX, int16_t tY ) {
  int16_t nX = tX / TileSize;
  int16_t nY = tY / TileSize;
  if ( Game->Level.CheckTile( nX, nY ) ) return 0xFF;
  return Game->Level.CheckObject( nX, nY );
}
bool Sprite::Falling( ) {
  return !CollisionCheckY( Down );
}
void Sprite::Gravity( ) {
  if ( vy < 6 ) vy++;
}
bool Sprite::CollisionCheckX( uint8_t direction ) {
  for ( uint8_t tY = 0; tY < ( Height() / TileSize ); tY++ ) {
    switch ( direction ) {
      case Left:
        if ( Collide( x-1, y+(tY*TileSize) ) || Collide( x-1, y+((tY+1)*TileSize)-1 ) ) return true;
        break;
      case Right:
        if ( Collide( x + Width(), y+(tY*TileSize) ) || Collide( x+Width(), y+((tY+1)*TileSize)-1 ) ) return true;
        break;
    }
  }
  return false;
}
bool Sprite::CollisionCheckY( uint8_t direction ) {
  for ( uint8_t tX = 0; tX < (Width()/TileSize); tX++ ) {
    switch ( direction ) {
      case Up:
        if ( Collide( x+(tX*TileSize), y-1 ) || Collide( x+((tX+1)*TileSize)-1, y-1 ) ) return true;
        break;
      case Down:
        if ( Collide( x+(tX*TileSize), y+Height() ) || Collide( x+((tX+1)*TileSize)-1, y+Height() ) ) return true;
        break;
    }
  }
  return false;
}
void Sprite::Move( ) {
  if ( Flags() & 1 ) {
    x += vx;
    y += vy;
    return;
  }
  if ( vy == 0 ) { // Start fall
    if ( Falling( ) ) Gravity( );
  }
  if ( vy > 0 ) { // Down
    for ( int16_t a = 0; a < vy; a++ ) {
      if ( Falling( ) ) {
        y++;
      }
      else { vy = 0; break; }
    }
    Gravity( );
  }
  if ( vy < 0 ) { // Up
    Gravity( );
    for ( int16_t a = 0; a > vy; a-- ) {
      if ( CollisionCheckY(Up) ) { HeadCollision(); vy = 0; break; }
      else y--;
    }
  }
  if ( vx > 0 ) { // Right
    for ( int16_t a = 0; a < vx; a++ ){
    if ( RightX() > Game->Level.MaxXPixel() ) break;
      if ( CollisionCheckX(Right) ) break;
      else x++;
    }
//  if ( !Game->MainHand.Used ) Mirrored = false;
  }
  if ( vx < 0 ) { // Left
    for ( int16_t a = 0; a > vx; a-- ){
      if ( x < Game->Level.MinXPixel() + 1 ) break;
      if ( CollisionCheckX(Left) ) break;
      else x--;
    }
//  if ( !Game->MainHand.Used ) Mirrored = true;
  }
}
bool Sprite::Jump( ) {
  if ( CollisionCheckY( Down ) ) { vy = -8; return true; }
  return false;
}
void Sprite::Duck( ) {
  if ( x < 64 ) return;
  if ( Collide( x, y+Height()+1 ) == STPipeCapLeft && Collide( RightX() , y+Height()+1 ) == STPipeCapRight ) {
    Game->SFX = SFX_Pipe;
    Game->Event = ETPipeDrop;
    Game->EventCounter = 0;
  }
}
void Sprite::HeadCollision( ) {
  if ( Flags() & 0b10 ) return;

  if ( Collide( x, y-1 ) == STTopPipeCapLeft && Collide( RightX(), y-1 ) == STTopPipeCapRight ) {
    if ( x < 64 ) return;
    Game->SFX = SFX_Pipe;
    Game->Event = ETPipeRise;
    Game->EventCounter = 0;
  }

  uint8_t LeftCheck = Collide( x, y-1 );
  uint8_t RightCheck = Collide( RightX(), y-1 );
  if ( LeftCheck == STQBlock || LeftCheck == STMushBlock ) {
    Game->Level.HandleObject( x / TileSize, (y-1) / TileSize );
  }
  if ( RightCheck == STQBlock || RightCheck == STMushBlock ) {
    Game->Level.HandleObject( RightX() / TileSize, (y-1) / TileSize );
  }
  
}
void Sprite::Draw( ) {
  if ( Masks() ) Game->Display->drawBitmap(
    x - Game->CameraX,
    y - Game->CameraY,
    MaskPointer( ), Width(), Height(), BLACK );
  Game->Display->drawBitmap(
    x - Game->CameraX,
    y - Game->CameraY,
    FramePointer( ),
    Width(), Height(), WHITE );
    
  if ( currentFrame+1 < MaxFrame() * CyclesPerFrame() ) currentFrame++;
  else currentFrame = 0;
}
int16_t Sprite::RightX( ) { return x+Width()-1; }
int16_t Sprite::BottomY( ) { return y+Height()-1; }

uint8_t AISprite::Speed( )        { return pgm_read_byte( SpriteData + SpriteSpeed ); }
uint8_t    AISprite::Intelligence( ) { return pgm_read_byte( SpriteData + SpriteIntelligence ); }
void AISprite::Activate( const uint8_t * DataPointer, int16_t tX, int16_t tY ) {
  SpriteData = DataPointer;
  Active = true;
  Facing = Left;
  LoadSprite( DataPointer, tX*TileSize, tY*TileSize );
  if ( DataPointer == BoltSprite ) {
    vx = -4;
    vy = 2;
  }
  Think();
}
void AISprite::Deactivate( ) {
  SpriteData = NULL;
  Active = false;
  Facing = 0;
  ClearSprite();
}
void AISprite::Think( ) {
  if   ( Intelligence() & 0b00000100 ) {
    Seek();
    if ( Intelligence() & 0b00001000 ) DetectJump();
  }
  else {
    if ( Intelligence() & 0b00000001 ) DetectWall();
    if ( Intelligence() & 0b00000010 ) DetectGap();
  }
  Move();
}
void AISprite::Seek( ) {
  if ( Game->Player.x + Game->Player.Width() < x ) {
    Facing = Left;
    vx = Speed() * -1;
  }
  if ( Game->Player.x > x + Width() ) {
    Facing = Right;
    vx = Speed();
  }
}
void AISprite::DetectJump( ) {
  if ( CollisionCheckX( Facing ) ) Jump();
  if ( Facing == Left ) {
    if ( !Collide( x-1, (RoomHeight*TileSize) - 1 ) ) Jump();
  }
  if ( Facing == Right ) {
    if ( !Collide( RightX()+1, (RoomHeight*TileSize) - 1 ) ) Jump();
  }
}
void AISprite::DetectWall( ) {
  if ( Facing == Left ) {
    if ( CollisionCheckX(Left) ) { Facing = Right; vx = 0; return; }
    else vx = Speed() * -1;
  }
  if ( Facing == Right ) {
    if ( CollisionCheckX(Right) ) { Facing = Left; vx = 0; return; }
    else vx = Speed();
  }
}
void AISprite::DetectGap( ) {
  if ( Facing == Left ) {
    if ( !Collide( x-1, BottomY()+1 ) ) { Facing = Right; vx = 0; return; }
    else vx = Speed() * -1;
  }
  if ( Facing == Right ) {
    if ( !Collide( RightX()+1, BottomY() + 1 ) ) { Facing = Left; vx = 0; return; }
    else vx = Speed();
  }
}

void Room::ClearRoom( ) {
  for ( int16_t a = 0; a < RoomBytes; a++ ) data[a] = 0;
}
void Room::SetTile( int16_t x, int16_t y ) {
  if ( x > RoomWidth || y > RoomHeight ) return;
  int16_t Index = ( RoomHeight/8 ) * x;
  if ( y < 8 ) data[ Index ]   |= 1 << y;
  else         data[ Index+1 ] |= 1 << (y - 8);
}
bool Room::ReadTile( int16_t x, int16_t y ) {
  if ( x > RoomWidth || y > RoomHeight ) return false;
  int16_t Index = ( RoomHeight/8 ) * x;
  if ( y < 8 ) {
    uint8_t Mask = 1 << y;
    if ( data[ Index ] & Mask ) return true;
  }
  else {
    uint8_t Mask = 1 << (y - 8);
    if ( data[ Index+1 ] & Mask ) return true;
  }
  return false;
}

void Map::GenerateRoom( int16_t RoomNum ) {
  randomSeed( Game->Seeds[ ( Game->MapNumber + RoomNum ) % GameSeeds ] * Game->MapNumber + RoomNum );
  rooms[RoomNum%MapRooms].ClearRoom();
  uint8_t Floor = random(RoomHeight-3,RoomHeight);
  uint8_t Ceiling = ( !( Game->MapNumber % 2 ) ) ? 8 : 0;
  int16_t Gap = 0;
  int16_t tSpawnBarrier = RoomNum*RoomWidth;
  if ( !RoomNum ) {
    if ( Ceiling ) AddTopPipe( 1, Ceiling + 1 );
    else AddPipe( 1, Floor-2 );
  }
  for ( int16_t x = 0; x < RoomWidth; x++ ) {
    if ( Ceiling ) rooms[RoomNum % MapRooms].SetTile(x, Ceiling);
    if ( !Gap ) {
      for ( int16_t b = Floor; b < RoomHeight; b++ ) {
        rooms[RoomNum % MapRooms].SetTile(x, b);
      }
      if ( RoomNum && ( RoomNum < LastRoom ) ) {
        if ( !random(10) ) { 
          Gap = random(2,5);
          if ( Ceiling ) Gap--;
        }
        else if ( !random(5)  ) {
          if ( !random(1) && Floor < RoomHeight-1 ) Floor++;
          else Floor--;
        }
        if ( tSpawnBarrier > SpawnBarrier ) {
          if ( !random( 8 ) ) {
            uint8_t MobSelector = random(20);
            if      ( MobSelector < 10 ) Game->AddMob( TriangleoSprite, tSpawnBarrier + x, Floor - 2 );
            else if ( MobSelector < 16 ) Game->AddMob( SmileoSprite, tSpawnBarrier + x, Floor - 2 );
            else if ( MobSelector < 19 ) {
              if ( RoomNum > 8 ) Game->AddMob( StarmanoSprite, tSpawnBarrier + x, Floor - 2 );
            }
            else { 
              if ( RoomNum > 8 ) Game->AddMob( BoltSprite, tSpawnBarrier + x, 2 );
            }
          }
          if ( !random( 16 ) && !Gap && Floor > Ceiling + 5 && x != RoomWidth-1 ) {
            int16_t y = random( max( Floor - 7, Ceiling + 2 ), Floor - 3 );
            if ( !random(4) ) AddObject ( STMushBlock, tSpawnBarrier + x, y );
            else              AddObject ( STQBlock, tSpawnBarrier + x, y );
          }
        }
      }
    }
    else Gap--;
  }
  if ( RoomNum == LastRoom ) {
    if ( Ceiling ) AddTopPipe ( MaxXTile() - 2, Ceiling + 1 );
    else AddPipe( MaxXTile() - 2, Floor-2 );
  }
  if ( tSpawnBarrier > SpawnBarrier ) SpawnBarrier = tSpawnBarrier;
}
void Map::AddPipe( int16_t x, int16_t y ) {
  AddObject( STPipeCapLeft,  x,   y );
  AddObject( STPipeCapRight, x+1, y );
  for ( uint8_t a = y+1; a < RoomHeight; a++ ) {
    AddObject( STPipeLeft,     x,   a );
    AddObject( STPipeRight,    x+1, a );
  }
}
void Map::AddTopPipe( int16_t x, int16_t y ) {
  AddObject( STTopPipeCapLeft,  x,   y+1 );
  AddObject( STTopPipeCapRight, x+1, y+1 );
  AddObject( STPipeLeft,     x,   y );
  AddObject( STPipeRight,    x+1, y );
}
void Map::AddObject( uint8_t type, int16_t tX, int16_t tY ) {
  if ( CheckObject( tX, tY ) ) return;
  else {
    objects[ObjectIndex].x = tX;
    objects[ObjectIndex].y = tY;
    objects[ObjectIndex].type = type;
    ObjectIndex++;
    if ( ObjectIndex == MapObjects ) ObjectIndex = 0;
  }
}
void Map::HandleObject( int16_t x, int16_t y ) {
  for ( int16_t a = 0; a < MapObjects; a++ ) {
    if ( objects[a].x == x && objects[a].y == y ) {
      switch ( objects[a].type ) {
        case STQBlock: 
          Game->Coins++;
          if ( !( Game->Coins % 20 ) ) {
            Game->Lives++;
            Game->SFX = SFX_Life;
          }
          else Game->SFX = SFX_Coin;
          objects[a].type = STBQBlock;
          break;
        case STMushBlock:
          Game->AddMob ( MushroomSprite, x, y-1 );
          objects[a].type = STBQBlock; break;
      }
    }
  }
}
void Map::RemoveObject( int16_t x, int16_t y ) {
  for ( int16_t a = 0; a < MapObjects; a++ ) {
    if ( objects[a].x == x && objects[a].y == y ) {
      objects[a].y = -1;
      return;
    }
  }
}
void Map::NewMap( ) {
  // Reset Variables
  ObjectIndex = 0; LastLoadLocation = 0; FirstRoom = 0; SpawnBarrier = 0;
  for ( uint8_t a = 0; a < MapObjects; a++ ) objects[a].y = -1;
  for ( uint8_t a = 0; a < SpriteCap; a++ ) Game->Mobs[a].Deactivate();

  // Seed for level length
  randomSeed( Game->Seeds[ Game->MapNumber % GameSeeds ] * Game->MapNumber );
  int16_t LowEnd = MinLevelWidth + random( Game->MapNumber );
  int16_t HighEnd = random( LowEnd, LowEnd + Game->MapNumber );
  LastRoom = random( LowEnd, HighEnd );

  for ( uint8_t a = 0; a < MapRooms; a++ ) GenerateRoom(a);
}
void Map::LoadMap( ) {
  int16_t RoomBeforePlayerIsIn = ( Game->Player.x / (RoomWidth*TileSize) ) - 1;
  if (RoomBeforePlayerIsIn < 0) RoomBeforePlayerIsIn = 0;
  if (RoomBeforePlayerIsIn > FirstRoom) {
    FirstRoom = RoomBeforePlayerIsIn;
    GenerateRoom( RoomBeforePlayerIsIn + MapRooms - 1 );
  }
}
bool Map::CheckTile( int16_t x, int16_t y ) {
  int16_t room = ( x / RoomWidth ) % MapRooms;
  return rooms[room].ReadTile ( x % RoomWidth, y );
}
uint8_t Map::CheckObject ( int16_t x, int16_t y ) {
  if ( y < 0 ) return 0;
  for ( int16_t a = 0; a < MapObjects; a++ ) {
    if ( ( objects[a].x == x ) && ( objects[a].y == y ) ) return objects[a].type;
  }
  return 0;
}
int16_t Map::MinXPixel() { return FirstRoom * RoomWidth * TileSize; }
int16_t Map::MaxXPixel() { return ( ( LastRoom + 1 ) * RoomWidth * TileSize ) - 1; }
int16_t Map::MaxYPixel() { return ( ( MapHeight + 1 ) * RoomHeight * TileSize ) - 1; }
int16_t Map::MinXTile() { return FirstRoom * RoomWidth; }
int16_t Map::MaxXTile() { return ( ( LastRoom + 1 ) * RoomWidth ) - 1; }
int16_t Map::MaxYTile() { return ( ( MapHeight + 1 ) * RoomHeight ) - 1; }

SquarioGame::SquarioGame( Arduboy2 * display ) {
  Display = display;
  Player.Game = this;
  Level.Game = this;
  for ( uint8_t a = 0; a < SpriteCap; a++ ) Mobs[a].Game = this;
}
void SquarioGame::NewGame( ) {
  Health = 0;
  Score = 0;
  DistancePoints = 0;
  Coins = 0;
  Lives = 1;
  MapNumber = 1;
  Player.LoadSprite( SmallSquarioSprite, 10, SpawnY() );
  StartLevel( );
}
void SquarioGame::StartLevel( ) {
  Event = ETPlaying;
  SFX = NULL;
  Level.NewMap( );
  while ( Player.Falling() ) Player.Move();
  AdjustCamera( );
}
int16_t SquarioGame::SpawnY() {
  if ( MapNumber % 2 ) return 0;
  else return 88;
}
void SquarioGame::ProcessButtons( ) {
  uint8_t MaxSpeed = ButtonState[ButtonRun] ? 4 : 3;
//if ( ButtonState[ButtonRun] ) MainHand.Use( );
  if ( !ButtonState[ButtonLeft] && !ButtonState[ButtonRight] ) {
    if ( Player.vx > 0 ) Player.vx--;
    if ( Player.vx < 0 ) Player.vx++;
  }
  if ( ButtonState[ButtonLeft] )  { Player.vx--; if ( Player.vx < MaxSpeed * -1 ) Player.vx = MaxSpeed * -1; }
  if ( ButtonState[ButtonRight] ) { Player.vx++; if ( Player.vx > MaxSpeed ) Player.vx = MaxSpeed; }
  if ( ButtonState[ButtonJump] ) {
    if ( Player.Jump() ) SFX = SFX_Jump;
  }
  if ( ButtonState[ButtonDown] ) Player.Duck();
}


void SquarioGame::AdjustCamera( ) {
  int16_t MaxX = Level.MaxXPixel() - WIDTH;
  int16_t MaxY = Level.MaxYPixel() - HEIGHT;
  int16_t MinX = Level.MinXPixel();
  CameraX = Player.x - (WIDTH/2); // Center X on player
  CameraY = Player.y - 8;

  // Constrain for map edges
  if ( CameraY > MaxY ) CameraY = MaxY;
  if ( CameraX > MaxX ) CameraX = MaxX;
  if ( CameraX < MinX ) CameraX = MinX;

  // Reload map data
//  if ( Level.LastLoadLocation > Player.x - 128 ) {
//    Level.LastLoadLocation = Player.x;
    Level.LoadMap();
//  }
//  int16_t lastChange = Level.LastLoadLocation - Player.x;
//  if ( lastChange > 128 || lastChange < -128 ) Level.LoadMap();
}


void SquarioGame::Cycle( ) {
  bool Death = false;
  int16_t MapPixelHeight = Level.MaxYPixel();
  ProcessButtons();
  if ( Event == ETPipeDrop && EventCounter < Player.Height()) {
    Player.y++;
    EventCounter++;
  }
  if ( Event == ETPipeRise && EventCounter < Player.Height()) {
    Player.y--;
    EventCounter++;
  }
  else if ( Event == ETDeath ) {
    if ( EventCounter > 25 ) Player.y--;
    else Player.y+=2;
    if ( Player.y > MapPixelHeight ) EventCounter = 0;
    else EventCounter--;
  }
  else if ( Event == ETPlaying ) {
    Player.Move();
    AdjustCamera();
  }
  for ( uint8_t a = 0; a < SpriteCap; a++ ) {
    if ( Mobs[a].Active ) {
      Mobs[a].Think();
      if ( Mobs[a].y > MapPixelHeight ) Mobs[a].Deactivate();
      else if ( TestCollision( &Player, &Mobs[a] ) ) {
        if ( Mobs[a].SpriteData == MushroomSprite ) {
          Mobs[a].Deactivate();
          Score += POINTSMushroom;
          SFX = SFX_Mushroom;
          if ( Player.SpriteData == SmallSquarioSprite ) Player.LoadSprite( BigSquarioSprite, Player.x, Player.y-8 );
          else if ( Health < 5 ) Health++;
        }
        else if ( Player.Falling() ) {
          Mobs[a].Deactivate();
          Score += POINTSKill;
          SFX = SFX_Hit;
          if ( ButtonState[ ButtonJump ] ) { Player.vy = -10; }
          else { Player.vy = -4; }          
        }
        else if ( !EventCounter ) {
          if ( Health > 0 ) Health--;
          else {
            if ( Player.Height() == TileSize ) Event = ETDeath;
            if ( Player.Height() > TileSize ) {
              Player.LoadSprite( SmallSquarioSprite, Player.x, Player.y+8 );
              SFX = SFX_Hit;
            }
          }
          EventCounter = 30;
        }
      }
    }
  }
  if ( Event == ETPlaying && Player.y > MapPixelHeight ) { Event = ETDeath; EventCounter = 25; }
  if ( Event == ETDeath && !EventCounter ) Die();
  if ( Event == ETPlaying && EventCounter ) EventCounter--;
  if ( ( Event == ETPipeDrop || Event == ETPipeRise ) && EventCounter == Player.Height() ) {
    EventCounter = 0;
    DistancePoints += Player.x / TileSize;
    MapNumber++;
    Player.x = 10;
    Player.y = SpawnY();
    StartLevel( );
  }
}


bool SquarioGame::TestCollision( Sprite * TestSprite1, AISprite * TestSprite2 ) {
  if ( TestRoughCollision( TestSprite1, TestSprite2 ) )
    if ( TestPixelCollision( TestSprite1, TestSprite2 ) ) return true;
  return false;
}


bool SquarioGame::TestRoughCollision( Sprite * TestSprite1, AISprite * TestSprite2 ) {
  if ( TestSprite1->IsIn ( TestSprite2->x,       TestSprite2->y ) ||
       TestSprite1->IsIn ( TestSprite2->RightX(),TestSprite2->y ) ||
       TestSprite1->IsIn ( TestSprite2->x,       TestSprite2->BottomY() ) ||
       TestSprite1->IsIn ( TestSprite2->RightX(),TestSprite2->BottomY() ) ) {
    return true;
  }
  return false;
}


bool SquarioGame::TestPixelCollision( Sprite * TestSprite1, AISprite * TestSprite2 ) {
  for ( int16_t a = max( TestSprite1->x, TestSprite2->x ); a <= min( TestSprite1->RightX(), TestSprite2->RightX() ); a++ ) {
    for ( int16_t b = max( TestSprite1->y, TestSprite2->y ); b <= min( TestSprite1->BottomY(), TestSprite2->BottomY() ); b++ ) {
      if ( TestSprite1->GetPixelAbsolute(a,b) ) {
        if ( TestSprite2->GetPixelAbsolute(a,b) ) return true;
      }
    }
  }
  return false;
}


void SquarioGame::Die( ) {
  Lives--;
  Draw();
  if ( Lives ) {
    Health = 0;
    Player.LoadSprite( SmallSquarioSprite, 10, SpawnY() );
    StartLevel( );
    delay(200);
  }
  else {
    DistancePoints += Player.x / TileSize;
    Event = ETOff;
    Display->drawRect(16,8,96,48, WHITE); // Box border
    Display->fillRect(17,9,94,46, BLACK); // Black out the inside
    Display->drawSlowXYBitmap(30,12,gameover,72,14,1);
    
    Display->setCursor(26,29); Display->print(F("Score"));
    Display->setCursor(26,37); Display->print(F("Dist."));
    Display->setCursor(26,45); Display->print(F("Total"));

    DiePrint( 29, Score );
    DiePrint( 37, DistancePoints );
    Score += DistancePoints;
    DiePrint( 45, Score );
    delay(1000);
  }
}


void SquarioGame::DiePrint( uint8_t y, uint16_t i ) {
  Display->setCursor( 96 - getTextOffset( i ), y );
  Display->print( i );
  Display->display( );
  delay(250);
  //while (!Display->buttonsState());
}


void SquarioGame::DrawMobs( ) {
  for ( uint8_t a = 0; a < SpriteCap; a++ ) {
    if ( Mobs[a].Active ) {
      if ( Mobs[a].RightX() - CameraX > 0 && Mobs[a].x - CameraX < 128 ) Mobs[a].Draw();
    }
  }
}


void SquarioGame::DrawMap( ) {
  int16_t mountainOffset = ( CameraX / 4 ) % 64;
  int16_t mountainYOffset = ( CameraY / 12 ) - 4;
  if ( MapNumber % 2 ) {
    Display->drawBitmap(  0 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
    Display->drawBitmap( 64 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
    Display->drawBitmap(128 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
  }
  else {
    for ( uint8_t a = 0; a < 196; a += 96 ) {
      Display->drawBitmap(  a - ( CameraX / 4 ) % 96, mountainYOffset+20, UndergroundBricks, 37, 24, 1 );
    }
  }
  for ( int16_t x = CameraX / TileSize; x < (CameraX / TileSize) + 17; x++ ) {
    for ( int16_t y = CameraY / TileSize; y < (CameraY / TileSize) + 9; y++ ) {
      if ( Level.CheckTile( x, y ) ) {
        Display->drawBitmap( x*TileSize - CameraX, y*TileSize - CameraY, tMask, TileSize, TileSize, BLACK );
        Display->drawBitmap( x*TileSize - CameraX, y*TileSize - CameraY, tBrick, TileSize, TileSize, WHITE );
      }
      else {
        const uint8_t * tempTile = 0;
        switch ( Level.CheckObject(x,y) ) {
          case STMushBlock:
          case STQBlock:        tempTile = tQBlock; break;
          case STBQBlock:       tempTile = tBQBlock; break;
          case STPipeCapLeft:   tempTile = tPipeCapLeft; break;
          case STPipeCapRight:  tempTile = tPipeCapRight; break;
          case STTopPipeCapLeft:   tempTile = tTopPipeCapLeft; break;
          case STTopPipeCapRight:  tempTile = tTopPipeCapRight; break;
          case STPipeLeft:      tempTile = tPipeLeft; break;
          case STPipeRight:     tempTile = tPipeRight; break;
        }
        if ( tempTile ) {
          Display->drawBitmap( x*TileSize - CameraX, y*TileSize - CameraY, tMask, TileSize, TileSize, BLACK );
          Display->drawBitmap( x*TileSize - CameraX, y*TileSize - CameraY, tempTile, TileSize, TileSize, WHITE );
        }
      }
    }
  }
}


void SquarioGame::DrawPlayer( ) {
  Player.Draw();
  if ( Health ) {
    for ( uint8_t a = 0; a < Health; a++ ) {
      Display->drawFastHLine( Player.x + 1 - CameraX, Player.y+11-(a*2)-CameraY, 6, WHITE );
      Display->drawFastHLine( Player.x + 1 - CameraX, Player.y+10-(a*2)-CameraY, 6, WHITE );
    }
  }  
}


void SquarioGame::Draw() {
  switch ( Event ) {
    case ETDeath:
    case ETPlaying:   DrawMap(); DrawMobs(); 
                      if ( !(EventCounter % 2) ) DrawPlayer();
                      break;
    case ETPipeDrop:
    case ETPipeRise:  DrawPlayer(); DrawMap(); DrawMobs(); break;
  }
}


void SquarioGame::AddMob( const uint8_t * DataPointer, int16_t x, int16_t y ) {
  int16_t Distances[ SpriteCap ];
  for ( uint8_t a = 0; a < SpriteCap; a++ ) {
    if ( !Mobs[a].Active ) { Mobs[a].Activate( DataPointer, x, y ); return; }
    Distances[a] = Player.x - Mobs[a].x;
    if ( Distances[a] < 0 ) Distances[a] *= -1;
  }
  uint8_t Distance = Distances[0];
  uint8_t Candidate = 0;
  for ( uint8_t a = 1; a < SpriteCap; a++ ) {
    if ( Distances[a] > Distance ) {
      Candidate = a;
      Distance = Distances[a];
    }
  }
  Mobs[Candidate].Activate( DataPointer, x, y );
}
void SquarioGame::ButtonPress( uint8_t pButton ) {
  if ( ButtonState[ pButton ] ) return;
  ButtonState[ pButton ] = true;
}
void SquarioGame::ButtonRelease( uint8_t pButton ) {
  if ( !ButtonState[ pButton ] ) return;
  ButtonState[ pButton ] = false;
}
void SquarioGame::ActivateButtonCD( ) {
  lastPress = millis();
}


bool SquarioGame::ButtonOffCD( ) {
  if ( millis() > lastPress + BUTTONCD ) return true;
  return false;
}


int16_t SquarioGame::getTextOffset(int16_t s) {
  if (s > 9999) { return 20; }
  if (s > 999) { return 15; }
  if (s > 99) { return 10; }
  if (s > 9) { return 5; }
  return 0;
}

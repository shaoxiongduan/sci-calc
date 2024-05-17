#ifndef SQUARIO_h
#define SQUARIO_h
#include <Arduboy2.h>
#include "DefinesImagesAndSounds.h"

enum SquarioButtons {
  ButtonLeft = 0,
  ButtonUp,
  ButtonRight,
  ButtonDown,
  ButtonJump,
  ButtonRun,
  NumButtons
};
enum Directions {
  Up,
  Down,
  Left,
  Right
};
enum ObjectTypes {
  STSquario = 0, // Sprites
  STBigSquario,
  STTriangleo,
  STStarmano,
  STSmileo,
  STBolt,
  
  STMushroom,

  STQBlock,  // Interactive Tiles
  STBQBlock,
  STMushBlock,
  STBricks,
  STPipeCapLeft,
  STPipeCapRight,
  STTopPipeCapLeft,
  STTopPipeCapRight,
  STPipeLeft,
  STPipeRight,
  
  NumObjectTypes
};
enum EventTypes {
  ETOff = 0,
  ETPlaying,
  ETDeath,
  ETPipeDrop,
  ETPipeRise,
  ETNum
};

class Room;
class Map;
class Sprite;
class AISprite;
class SquarioGame;

class Sprite {
  public:
    void LoadSprite( const uint8_t * DataPointer, int16_t tX, int16_t tY );
    void ClearSprite( );
    bool IsIn ( int16_t tX, int16_t tY );
    bool IsInTopHalf ( int16_t tX, int16_t tY );
    virtual bool GetPixelAbsolute( int16_t tX, int16_t tY );
    uint8_t  Collide( int16_t tX, int16_t tY );
    bool CollisionCheckX( uint8_t  direction );
    bool CollisionCheckY( uint8_t  direction );
    void HeadCollision( );
    bool Falling( );
    void Gravity( );
    void Move( );
    bool Jump( );
    void Duck( );
    void Draw( );
    
    uint8_t Width( );
    uint8_t Height( );
    uint8_t Masks( );
    uint8_t MaxFrame( );
    uint8_t CyclesPerFrame( );
    uint8_t  Flags( );
    const uint8_t * FramePointer( );
    const uint8_t * MaskPointer( );
    int16_t RightX( );
    int16_t BottomY( );

    SquarioGame         * Game;
    const uint8_t * SpriteData;
    int16_t                   x, y, vx, vy;
    int16_t                   currentFrame;
    bool                  Mirrored;

};
class AISprite : public Sprite {
  public:
    void Activate( const uint8_t * DataPointer, int16_t tX, int16_t tY );
    void Deactivate( );
    void Think( );
    void Seek( );
    void DetectJump( );
    void DetectWall( );
    void DetectGap( );
    
    uint8_t Speed( );
    uint8_t  Intelligence( );
    bool                  Active;
    uint8_t                   Facing;
};
class InteractiveObject {
  public:
    int16_t x, y;
    uint8_t  type;
};
class Room {
  public:
    void ClearRoom( );
    void SetTile( int16_t x, int16_t y );
    bool ReadTile( int16_t x, int16_t y );
    uint8_t          data[ RoomBytes ];
};
class Map {
  public:
    void NewMap( );
    void LoadMap( );
    void GenerateRoom( int16_t RoomNum );
    void AddObject( uint8_t  type, int16_t x, int16_t y );
    void HandleObject ( int16_t x, int16_t y );
    void RemoveObject( int16_t x, int16_t y );
    uint8_t  CheckObject( int16_t x, int16_t y );
    bool CheckTile( int16_t x, int16_t y );
    void AddPipe( int16_t x, int16_t y );
    void AddTopPipe( int16_t x, int16_t y );

    int16_t MinXPixel();
    int16_t MaxXPixel();
    int16_t MaxYPixel();
    int16_t MinXTile();
    int16_t MaxXTile();
    int16_t MaxYTile();
    
    SquarioGame         * Game;
    Room                  rooms[MapRooms];
    InteractiveObject     objects[MapObjects];
    int16_t                   ObjectIndex;
    int16_t                   RandomChance;
    int16_t                   FirstRoom, LastRoom, MapHeight, LastLoadLocation, SpawnBarrier;
};
class SquarioGame {
  public:
    SquarioGame(Arduboy2 * display);
    void NewGame( );
    void StartLevel( );
    int16_t  SpawnY( );
    void Cycle( );
    bool TestCollision( Sprite * TestSprite1, AISprite * TestSprite2 );
    bool TestRoughCollision( Sprite * TestSprite1, AISprite * TestSprite2 );
    bool TestPixelCollision( Sprite * TestSprite1, AISprite * TestSprite2 );
    void Draw( );
    void Die( );
    void DiePrint( uint8_t y, uint16_t  i );
    void DrawMap( );
    void DrawPlayer( );
    void DrawMobs( );
    void AddMob( const uint8_t * DataPointer, int16_t x, int16_t y );
    void AdjustCamera( );
    void ProcessButtons( );
    void ButtonPress( uint8_t pButton );
    void ButtonRelease( uint8_t pButton );
    bool ButtonState[ NumButtons ];
    void ActivateButtonCD( );
    bool ButtonOffCD( );
    int16_t getTextOffset( int16_t s );
    
    Arduboy2             * Display;
    Sprite                Player;
    AISprite              Mobs[ SpriteCap ];
    Map                   Level;

    int16_t                   Health;
    uint16_t           Score;
    uint16_t           DistancePoints;
    int16_t                   Coins, Lives, MapNumber;
    uint8_t                   Inventory;
    int16_t                   CameraX, CameraY;
    uint8_t                   Event;
    int16_t                   EventCounter;
    const uint8_t  *          SFX;
    uint8_t                   Seeds[ GameSeeds ];
    unsigned long         lastPress;
};


#endif

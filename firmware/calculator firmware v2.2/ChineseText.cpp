#include "ChineseText.h"

ChineseText::ChineseText(int type) : UIElement() {
    this -> type = type;
        this -> pos = 0;
}





void ChineseText::setType(int type) {
    this -> type = type;
    this -> pos = 0;
}


void ChineseText::init() {
    
}

void ChineseText::activate() {
    currentElement = this;
}


void ChineseText::draw() {
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    if (this -> type == 1) {
        if (this -> pos == 0) {
            u8g2.setCursor(0, 12);
            u8g2.print("君子曰：学不可以已。青，取之于蓝，而青于蓝");
            u8g2.setCursor(0, 24);
            u8g2.print("；冰，水为之，而寒于水。木直中绳，（车柔）");
            u8g2.setCursor(0, 36);
            u8g2.print("以为轮，其曲中规。虽有槁暴，不复挺者，（车");
            u8g2.setCursor(0, 48);
            u8g2.print("柔）使之然也。故木受绳则直，金就砺则利，君");
            u8g2.setCursor(0, 60);
            u8g2.print("子博学而日参省乎己，则知明而行无过矣。吾尝");
        }
        if (this -> pos == 1) {
            u8g2.setCursor(0, 12);
            u8g2.print("终日而思矣，不如须臾之所学也；吾尝（足支）");
            u8g2.setCursor(0, 24);
            u8g2.print("而望矣，不如登高之博见也。登高而招，臂非加");
            u8g2.setCursor(0, 36);
            u8g2.print("长也，而见者远；顺风而呼，声非加疾也，而闻");
            u8g2.setCursor(0, 48);
            u8g2.print("者彰。假舆马者，非利足也，而致千里；假舟楫");
            u8g2.setCursor(0, 60);
            u8g2.print("者，非能水也，而绝江河。君子生非异也，善假");
        }
        if (this -> pos == 2) {
            u8g2.setCursor(0, 12);
            u8g2.print("于物也。积土成山，风雨兴焉；积水成渊，蛟龙");
            u8g2.setCursor(0, 24);
            u8g2.print("生焉；积善成德，而神明自得，圣心备焉。故不");
            u8g2.setCursor(0, 36);
            u8g2.print("积跬步，无以至千里；不积小流，无以成江海。");
            u8g2.setCursor(0, 48);
            u8g2.print("骐骥一跃，不能十步；驽马十驾，功在不舍。锲");
            u8g2.setCursor(0, 60);
            u8g2.print("而舍之，朽木不折；锲而不舍，金石可镂。蚓无");
        }
        if (this -> pos == 3) {
            u8g2.setCursor(0, 12);
            u8g2.print("爪牙之利，筋骨之强，上食埃土，下饮黄泉，用");
            u8g2.setCursor(0, 24);
            u8g2.print("心一也。蟹六跪而二螯，非蛇鳝之穴无可寄托者");
            u8g2.setCursor(0, 36);
            u8g2.print("，用心躁也。");
        }

    }
    if (this -> type == 2) {
        if (this -> pos == 0) {
            u8g2.setCursor(0, 12);
            u8g2.print("六王毕，四海一，蜀山兀，阿房出。覆压三百余");
            u8g2.setCursor(0, 24);
            u8g2.print("里，隔离天日。骊山北构而西折，直走咸阳。二");
            u8g2.setCursor(0, 36);
            u8g2.print("川溶溶，流入宫墙。五步一楼，十步一阁；廊腰");
            u8g2.setCursor(0, 48);
            u8g2.print("缦回，檐牙高啄；各抱地势，钩心斗角。盘盘焉");
            u8g2.setCursor(0, 60);
            u8g2.print("，囷囷焉，蜂房水涡，矗不知其几千万落。长桥");
        }
        if (this -> pos == 1) {
            u8g2.setCursor(0, 12);
            u8g2.print("卧波，未云何龙？复道行空，不霁何虹？高低冥");
            u8g2.setCursor(0, 24);
            u8g2.print("迷，不知西东。歌台暖响，春光融融；舞殿冷袖");
            u8g2.setCursor(0, 36);
            u8g2.print("，风雨凄凄。一日之内，一宫之间，而气候不齐");
            u8g2.setCursor(0, 48);
            u8g2.print("。(不知其 一作：不知乎；西东 一作：东西");
            u8g2.setCursor(0, 60);
            u8g2.print(")妃嫔媵嫱，王子皇孙，辞楼下殿，辇来于秦。");
        }
        if (this -> pos == 2) {
            u8g2.setCursor(0, 12);
            u8g2.print("朝歌夜弦，为秦宫人。明星荧荧，开妆镜也；绿");
            u8g2.setCursor(0, 24);
            u8g2.print("云扰扰，梳晓鬟也；渭流涨腻，弃脂水也；烟斜");
            u8g2.setCursor(0, 36);
            u8g2.print("雾横，焚椒兰也。雷霆乍惊，宫车过也；辘辘远");
            u8g2.setCursor(0, 48);
            u8g2.print("听，杳不知其所之也。一肌一容，尽态极妍，缦");
            u8g2.setCursor(0, 60);
            u8g2.print("立远视，而望幸焉。有不见者三十六年。燕赵之");
        }
        if (this -> pos == 3) {
            u8g2.setCursor(0, 12);
            u8g2.print("收藏，韩魏之经营，齐楚之精英，几世几年，剽");
            u8g2.setCursor(0, 24);
            u8g2.print("掠其人，倚叠如山。一旦不能有，输来其间。鼎");
            u8g2.setCursor(0, 36);
            u8g2.print("铛玉石，金块珠砾，弃掷逦迤，秦人视之，亦不");
            u8g2.setCursor(0, 48);
            u8g2.print("甚惜。(有不见者 一作：有不得见者)嗟乎！");
            u8g2.setCursor(0, 60);
            u8g2.print("一人之心，千万人之心也。秦爱纷奢，人亦念其");
        }
        if (this -> pos == 4) {
            u8g2.setCursor(0, 12);
            u8g2.print("家。奈何取之尽锱铢，用之如泥沙？使负栋之柱");
            u8g2.setCursor(0, 24);
            u8g2.print("，多于南亩之农夫；架梁之椽，多于机上之工女");
            u8g2.setCursor(0, 36);
            u8g2.print("；钉头磷磷，多于在庾之粟粒；瓦缝参差，多于");
            u8g2.setCursor(0, 48);
            u8g2.print("周身之帛缕；直栏横槛，多于九土之城郭；管弦");
            u8g2.setCursor(0, 60);
            u8g2.print("呕哑，多于市人之言语。使天下之人，不敢言而");
        }
        if (this -> pos == 5) {
            u8g2.setCursor(0, 12);
            u8g2.print("敢怒。独夫之心，日益骄固。戍卒叫，函谷举，");
            u8g2.setCursor(0, 24);
            u8g2.print("楚人一炬，可怜焦土！呜呼！灭六国者六国也，");
            u8g2.setCursor(0, 36);
            u8g2.print("非秦也；族秦者秦也，非天下也。嗟乎！使六国");
            u8g2.setCursor(0, 48);
            u8g2.print("各爱其人，则足以拒秦；使秦复爱六国之人，则");
            u8g2.setCursor(0, 60);
            u8g2.print("递三世可至万世而为君，谁得而族灭也？秦人不");
        }
        if (this -> pos == 6) {
            u8g2.setCursor(0, 12);
            u8g2.print("暇自哀，而后人哀之；后人哀之而不鉴之，亦使");
            u8g2.setCursor(0, 24);
            u8g2.print("后人而复哀后人也。");
        }
    }
    if (this -> type == 3) {
        if (this -> pos == 0) {
            u8g2.setCursor(0, 12);
            u8g2.print("六国破灭，非兵不利，战不善，弊在赂秦。赂秦");
            u8g2.setCursor(0, 24);
            u8g2.print("而力亏，破灭之道也。或曰：六国互丧，率赂秦");
            u8g2.setCursor(0, 36);
            u8g2.print("耶？曰：不赂者以赂者丧。盖失强援，不能独完");
            u8g2.setCursor(0, 48);
            u8g2.print("。故曰：弊在赂秦也。秦以攻取之外，小则获邑");
            u8g2.setCursor(0, 60);
            u8g2.print("，大则得城。较秦之所得，与战胜而得者，其实");
        }
        if (this -> pos == 1) {
            u8g2.setCursor(0, 12);
            u8g2.print("百倍；诸侯之所亡，与战败而亡者，其实亦百倍");
            u8g2.setCursor(0, 24);
            u8g2.print("。则秦之所大欲，诸侯之所大患，固不在战矣。");
            u8g2.setCursor(0, 36);
            u8g2.print("思厥先祖父，暴霜露，斩荆棘，以有尺寸之地。");
            u8g2.setCursor(0, 48);
            u8g2.print("子孙视之不甚惜，举以予人，如弃草芥。今日割");
            u8g2.setCursor(0, 60);
            u8g2.print("五城，明日割十城，然后得一夕安寝。起视四境");
        }
        if (this -> pos == 2) {
            u8g2.setCursor(0, 12);
            u8g2.print("，而秦兵又至矣。然则诸侯之地有限，暴秦之欲");
            u8g2.setCursor(0, 24);
            u8g2.print("无厌，奉之弥繁，侵之愈急。故不战而强弱胜负");
            u8g2.setCursor(0, 36);
            u8g2.print("已判矣。至于颠覆，理固宜然。古人云：“以地");
            u8g2.setCursor(0, 48);
            u8g2.print("事秦，犹抱薪救火，薪不尽，火不灭。”此言得");
            u8g2.setCursor(0, 60);
            u8g2.print("之。齐人未尝赂秦，终继五国迁灭，何哉？与嬴");
        }
        if (this -> pos == 3) {
            u8g2.setCursor(0, 12);
            u8g2.print("而不助五国也。五国既丧，齐亦不免矣。燕赵之");
            u8g2.setCursor(0, 24);
            u8g2.print("君，始有远略，能守其土，义不赂秦。是故燕虽");
            u8g2.setCursor(0, 36);
            u8g2.print("小国而后亡，斯用兵之效也。至丹以荆卿为计，");
            u8g2.setCursor(0, 48);
            u8g2.print("始速祸焉。赵尝五战于秦，二败而三胜。后秦击");
            u8g2.setCursor(0, 60);
            u8g2.print("赵者再，李牧连却之。洎牧以谗诛，邯郸为郡，");
        }
        if (this -> pos == 4) {
            u8g2.setCursor(0, 12);
            u8g2.print("惜其用武而不终也。且燕赵处秦革灭殆尽之际，");
            u8g2.setCursor(0, 24);
            u8g2.print("可谓智力孤危，战败而亡，诚不得已。向使三国");
            u8g2.setCursor(0, 36);
            u8g2.print("各爱其地，齐人勿附于秦，刺客不行，良将犹在");
            u8g2.setCursor(0, 48);
            u8g2.print("，则胜负之数，存亡之理，当与秦相较，或未易");
            u8g2.setCursor(0, 60);
            u8g2.print("量。呜呼！以赂秦之地封天下之谋臣，以事秦之");
        }
        if (this -> pos == 5) {
            u8g2.setCursor(0, 12);
            u8g2.print("心礼天下之奇才，并力西向，则吾恐秦人食之不");
            u8g2.setCursor(0, 24);
            u8g2.print("得下咽也。悲夫！有如此之势，而为秦人积威之");
            u8g2.setCursor(0, 36);
            u8g2.print("所劫，日削月割，以趋于亡。为国者无使为积威");
            u8g2.setCursor(0, 48);
            u8g2.print("之所劫哉！夫六国与秦皆诸侯，其势弱于秦，而");
            u8g2.setCursor(0, 60);
            u8g2.print("犹有可以不赂而胜之之势。苟以天下之大，下而");
        }
        if (this -> pos == 6) {
            u8g2.setCursor(0, 12);
            u8g2.print("从六国破亡之故事，是又在六国下矣。");
        }
    }

    u8g2.setFont(u8g2_font_profont10_mf);
    //u8g2.drawStr(this -> x, this -> y, this -> text.substr(0, min(int(this -> text.size()), this -> width / 5)).c_str());
}

void ChineseText::update() {

    draw();
    if (kb.getRisingEdgeKey() == std::make_pair(1, 1)) {
        this -> pos = max(this -> pos - 1, 0);
    }
    if (kb.getRisingEdgeKey() == std::make_pair(3, 1)) {
        this -> pos = min(this -> pos + 1, 7);
    }
    if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        goBack();
    }
}
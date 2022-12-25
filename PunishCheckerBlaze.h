#ifndef PUNISH_CHECKER_BLAZE
#define PUNISH_CHECKER_BLAZE

class PunishCheckerBlaze
{
private:
    const int WHITE_R = 255;
    const int WHITE_G = 251;
    const int WHITE_B = 255;
    
    HWND _virtuaFighterWindow;
    HDC dc;

    int frameAdvantage;
    bool didPkCounter();
    bool didCuffisCounter();
    bool didKneeCounter();
    bool checkPoint(int x, int y, int r, int g, int b);
    void playSuccessSound();
    void playFailureSound();
    
    void getAdvantageAmount();
    void judgePunishment();
public:
    PunishCheckerBlaze(HWND virtuaFighterWindow);
    void giveFeedback();    
};

#endif
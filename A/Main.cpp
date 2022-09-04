# include <Siv3D.hpp>

void Main()
{
    int64 pX = 400, pY = 500, pR = 15;
    Circle p = Circle{ pX, pY, pR };
    Stopwatch s;
    s.start();
    int64 bX[10] = {0};
    int64 bY[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    Circle b[10];
    int64 bi = 0, bNum = 0, shotWaitTime = 11;
    Triangle e[120];
    double eX[120] = {0};
    double eY[120] = {-1};
    double eA[120];
    int64 ei = 0, eNum = 0;

    for ( int i = 0; i < 120; i++ ) {
        eA[i] = Random<double>(0.0, 360.0);
    }

    while (System::Update()) {
        ClearPrint();
        Print << U"PlayerPos: " << pX << U"," << pY;
        Print << U"objs: " << 1 + bNum + eNum;
        Print << U"time: " << s.s();

        if ( KeyUp.pressed() ) { pY -= 2; }
        if ( KeyDown.pressed() ) { pY += 2; }
        if ( KeyRight.pressed() ) { pX += 2; }
        if ( KeyLeft.pressed() ) { pX -= 2; }

        if ( pX > 800 ) { pX = 800; }
        if ( pX < 0 ) { pX = 0; }
        if ( pY > 600 ) { pY = 600; }
        if ( pY < 0 ) { pY = 0; }

        if ( KeyZ.pressed() && (shotWaitTime > 10) ) {
            if( bi >= 10 ) {
                bi = 0;
            }
            shotWaitTime = 0;
            bX[bi] = pX;
            bY[bi] = pY;
            bi++;
        }
        else {
            if( shotWaitTime <= 11 ) {
                shotWaitTime++;
            }
        }

        int imano_bNum = 10;
        for ( int i = 0; i < 10; i++ ) {
            if( bY[i] < 0 ) {
                imano_bNum--;
            }
            bNum = imano_bNum;
        }

        for ( int j = 0; j < 10; j++ ) {
            if( bY[j] >= 0 ) {
                b[j] = Circle{bX[j], bY[j], 7}.draw();
            }
        }

        for ( int k = 0; k < 10; k++ ) {
            if( bY[k] >= 0 ) {
                bY[k] -= 5;
            }
        }

        imano_bNum = 10;
        for ( int l = 0; l < 10; l++ ) {
            if( bY[l] < 0 ) {
                imano_bNum--;
            }
            bNum = imano_bNum;
        }

        p = Circle{ pX, pY, pR };
        p.draw();

        if ( s.s() % 2 == 0 ) {
            Print << U"ei:" << ei;
            if ( ei >= 120 ) {
                ei = 0;
            }
            eX[ei] = Random<int>(0, 800);
            eY[ei] = 0;
            e[ei] = Triangle{ eX[ei], eY[ei], 20 }.draw();
            ei++;
        }

        for ( int i = 0; i < 120; i++ ) {
            if( eY[i] <= 600 ) {
                e[i] = Triangle{ eX[i], eY[i], 20 }.rotated(eA[i]).draw();
                eA[i] += 2;
            }
        }

        for ( int i = 0; i < 120; i++ ) {
            if( eY[i] <= 600 ) {
                eY[i] += 3;
            }
        }

        int imano_eNum = 0;
        for ( int i = 0; i < 120; i++ ) {
            if( eY[i] <= 600 && eY[i] >= 0 ) {
                imano_eNum++;
            }
            eNum = imano_eNum;
        }

    }
}

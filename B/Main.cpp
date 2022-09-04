# include <Siv3D.hpp>
# include "GameMain.hpp"

void Main()
{
    GameMain gm;
    while (System::Update()) {
        gm.runOneDelta();
    }
}

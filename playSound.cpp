#include "playSound.h"
void selectSound() {
    PlaySound(TEXT("music\\select.wav"),NULL, SND_ASYNC);
}

void correctSound() {
    PlaySound(TEXT("music\\correct.wav"),NULL, SND_ASYNC);
}

void wrongSound() {
    PlaySound(TEXT("music\\wrong.wav"),NULL, SND_ASYNC);
}

void menuSound() {
    PlaySound(TEXT("music\\menu.wav"),NULL, SND_ASYNC);
}

void endSound() {
    PlaySound(TEXT("music\\end.wav"),NULL, SND_ASYNC);
}
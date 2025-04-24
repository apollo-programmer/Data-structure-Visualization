#include <GUI/Console.h>

Console::Console(){
    this->Controller = {controllerPosition.x-controllerSize.x/2.0f,controllerPosition.y-controllerSize.y/2.0f,controllerSize.x,controllerSize.y};
        
    this->Play.setSize(controllerButtonSize);
    this->Play.setPosition(controllerPosition);
    this->Play.setTexture(playButtonTheme);

    this->Next.setSize(controllerButtonSize);
    this->Next.setPosition({controllerPosition.x+(controllerButtonSize.x+15),controllerPosition.y});
    this->Next.setTexture(nextButtonTheme);

    this->Prev.setSize(controllerButtonSize);
    this->Prev.setPosition({controllerPosition.x-(controllerButtonSize.x+15),controllerPosition.y});
    this->Prev.setTexture(prevButtonTheme);

    this->End.setSize(controllerButtonSize);
    this->End.setPosition({controllerPosition.x+2*(controllerButtonSize.x+15),controllerPosition.y});
    this->End.setTexture(endButtonTheme);

    this->Start.setSize(controllerButtonSize);
    this->Start.setPosition({controllerPosition.x-2*(controllerButtonSize.x+15),controllerPosition.y});
    this->Start.setTexture(startButtonTheme);
}

bool Console::isPlayPressed(){
    return Play.isPressed();
}

bool Console::isNextPressed(){
    return Next.isPressed();
}

bool Console::isPrevPressed(){
    return Prev.isPressed();
}

bool Console::isEndPressed(){
    return End.isPressed();
}

bool Console::isStartPressed(){
    return Start.isPressed();
}

void Console::updateController(){
    if(isEnd) Play.setTexture(reloadButtonTheme);
    else if(isPause) Play.setTexture(playButtonTheme);
    else Play.setTexture(pauseButtonTheme);
    Next.setTexture(nextButtonTheme);
    Prev.setTexture(prevButtonTheme);
    End.setTexture(endButtonTheme);
    Start.setTexture(startButtonTheme);
    Play.update();
    Next.update();
    Prev.update();
    End.update();
    Start.update();
}

void Console::drawController(){
    DrawRectangleRounded(Controller,0,0,dataTitleColor);
    DrawRectangleLinesEx(Controller,3,outlineButtonColor);
    Play.drawRectangleRounded(100);
    Next.drawRectangleRounded(100);
    Prev.drawRectangleRounded(100);
    End.drawRectangleRounded(100);
    Start.drawRectangleRounded(100);
    Play.drawOutlineRounded(100,0,3);
    Next.drawOutlineRounded(100,0,3);
    Prev.drawOutlineRounded(100,0,3);
    End.drawOutlineRounded(100,0,3);
    Start.drawOutlineRounded(100,0,3);
    Play.drawTexture();
    Next.drawTexture();
    Prev.drawTexture();
    End.drawTexture();
    Start.drawTexture();
}

void Console::setEnd(){
    isEnd=true;
}

void Console::deEnd(){
    isEnd=false;
}

void Console::setPause(){
    isPause=true;
}

void Console::dePause(){
    isPause=false;
}
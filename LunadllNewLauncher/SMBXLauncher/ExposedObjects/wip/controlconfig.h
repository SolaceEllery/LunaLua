#ifndef CONTROLCONFIG_H
#define CONTROLCONFIG_H

#include <QObject>
#include <PGE_File_Formats/file_formats.h>

struct playerInputs {
    int up;
    int down;
    int left;
    int right;
    int jump;
    int run;
    int dropitem;
    int pause;
    int altjump;
    int altrun;
    int special;
    int leftTrigger;
    int rightTrigger;
    
    int j_jump;
    int j_run;
    int j_dropitem;
    int j_pause;
    int j_altjump;
    int j_altrun;

    int controllerType;

    // Constructor
    playerInputs()
    {
        Reset();
    }

    // Reset function
    void Reset()
    {
        up = 38;
        down = 40;
        left = 37;
        right = 39;
        jump = 88; // VK_Z is the default config for 1.3, I switched them for my own consistency
        run = 90; // VK_X is the default config for 1.3, I switched them for my own consistency
        dropitem = 16;
        pause = 27;
        altjump = 65;
        altrun = 83;
        special = 68;
        leftTrigger = 81;
        rightTrigger = 87;
        
        j_jump = 0;
        j_run = 3;
        j_dropitem = 6;
        j_pause = 7;
        j_altjump = 4;
        j_altrun = 5;

        controllerType = 0;
    }
};

extern playerInputs players[199];
extern std::string m_configFilenameAndPath;

class ControlConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenUpdated)
    Q_PROPERTY(unsigned int controllerType1 READ controllerType1 WRITE setControllerType1 NOTIFY controllerType1Updated)
    Q_PROPERTY(unsigned int keyboardUp1 READ keyboardUp1 WRITE setKeyboardUp1 NOTIFY keyboardUp1Updated)
    Q_PROPERTY(unsigned int keyboardDown1 READ keyboardDown1 WRITE setKeyboardDown1 NOTIFY keyboardDown1Updated)
    Q_PROPERTY(unsigned int keyboardLeft1 READ keyboardLeft1 WRITE setKeyboardLeft1 NOTIFY keyboardLeft1Updated)
    Q_PROPERTY(unsigned int keyboardRight1 READ keyboardRight1 WRITE setKeyboardRight1 NOTIFY keyboardRight1Updated)
    Q_PROPERTY(unsigned int keyboardRun1 READ keyboardRun1 WRITE setKeyboardRun1 NOTIFY keyboardRun1Updated)
    Q_PROPERTY(unsigned int keyboardJump1 READ keyboardJump1 WRITE setKeyboardJump1 NOTIFY keyboardJump1Updated)
    Q_PROPERTY(unsigned int keyboardDrop1 READ keyboardDrop1 WRITE setKeyboardDrop1 NOTIFY keyboardDrop1Updated)
    Q_PROPERTY(unsigned int keyboardPause1 READ keyboardPause1 WRITE setKeyboardPause1 NOTIFY keyboardPause1Updated)
    Q_PROPERTY(unsigned int keyboardAltJump1 READ keyboardAltJump1 WRITE setKeyboardAltJump1 NOTIFY keyboardAltJump1Updated)
    Q_PROPERTY(unsigned int keyboardAltRun1 READ keyboardAltRun1 WRITE setKeyboardAltRun1 NOTIFY keyboardAltRun1Updated)
    Q_PROPERTY(unsigned int joystickRun1 READ joystickRun1 WRITE setJoystickRun1 NOTIFY joystickRun1Updated)
    Q_PROPERTY(unsigned int joystickJump1 READ joystickJump1 WRITE setJoystickJump1 NOTIFY joystickJump1Updated)
    Q_PROPERTY(unsigned int joystickDrop1 READ joystickDrop1 WRITE setJoystickDrop1 NOTIFY joystickDrop1Updated)
    Q_PROPERTY(unsigned int joystickPause1 READ joystickPause1 WRITE setJoystickPause1 NOTIFY joystickPause1Updated)
    Q_PROPERTY(unsigned int joystickAltJump1 READ joystickAltJump1 WRITE setJoystickAltJump1 NOTIFY joystickAltJump1Updated)
    Q_PROPERTY(unsigned int joystickAltRun1 READ joystickAltRun1 WRITE setJoystickAltRun1 NOTIFY joystickAltRun1Updated)

    Q_PROPERTY(unsigned int controllerType2 READ controllerType2 WRITE setControllerType2 NOTIFY controllerType2Updated)
    Q_PROPERTY(unsigned int keyboardUp2 READ keyboardUp2 WRITE setKeyboardUp2 NOTIFY keyboardUp2Updated)
    Q_PROPERTY(unsigned int keyboardDown2 READ keyboardDown2 WRITE setKeyboardDown2 NOTIFY keyboardDown2Updated)
    Q_PROPERTY(unsigned int keyboardLeft2 READ keyboardLeft2 WRITE setKeyboardLeft2 NOTIFY keyboardLeft2Updated)
    Q_PROPERTY(unsigned int keyboardRight2 READ keyboardRight2 WRITE setKeyboardRight2 NOTIFY keyboardRight2Updated)
    Q_PROPERTY(unsigned int keyboardRun2 READ keyboardRun2 WRITE setKeyboardRun2 NOTIFY keyboardRun2Updated)
    Q_PROPERTY(unsigned int keyboardJump2 READ keyboardJump2 WRITE setKeyboardJump2 NOTIFY keyboardJump2Updated)
    Q_PROPERTY(unsigned int keyboardDrop2 READ keyboardDrop2 WRITE setKeyboardDrop2 NOTIFY keyboardDrop2Updated)
    Q_PROPERTY(unsigned int keyboardPause2 READ keyboardPause2 WRITE setKeyboardPause2 NOTIFY keyboardPause2Updated)
    Q_PROPERTY(unsigned int keyboardAltJump2 READ keyboardAltJump2 WRITE setKeyboardAltJump2 NOTIFY keyboardAltJump2Updated)
    Q_PROPERTY(unsigned int keyboardAltRun2 READ keyboardAltRun2 WRITE setKeyboardAltRun2 NOTIFY keyboardAltRun2Updated)
    Q_PROPERTY(unsigned int joystickRun2 READ joystickRun2 WRITE setJoystickRun2 NOTIFY joystickRun2Updated)
    Q_PROPERTY(unsigned int joystickJump2 READ joystickJump2 WRITE setJoystickJump2 NOTIFY joystickJump2Updated)
    Q_PROPERTY(unsigned int joystickDrop2 READ joystickDrop2 WRITE setJoystickDrop2 NOTIFY joystickDrop2Updated)
    Q_PROPERTY(unsigned int joystickPause2 READ joystickPause2 WRITE setJoystickPause2 NOTIFY joystickPause2Updated)
    Q_PROPERTY(unsigned int joystickAltJump2 READ joystickAltJump2 WRITE setJoystickAltJump2 NOTIFY joystickAltJump2Updated)
    Q_PROPERTY(unsigned int joystickAltRun2 READ joystickAltRun2 WRITE setJoystickAltRun2 NOTIFY joystickAltRun2Updated)

public:
    explicit ControlConfig(QObject *parent = 0);
    explicit ControlConfig(const QString& configFilename, QObject *parent = 0);

    void setDefaults();

    bool fullscreen() const
    {
        return m_data.fullScreen;
    }

    unsigned int controllerType1() const
    {
        return players[0].controllerType;
    }

    unsigned int keyboardUp1() const
    {
        return players[0].up;
    }

    unsigned int keyboardDown1() const
    {
        return players[0].down;
    }

    unsigned int keyboardLeft1() const
    {
        return players[0].left;
    }

    unsigned int keyboardRight1() const
    {
        return players[0].right;
    }

    unsigned int keyboardRun1() const
    {
        return players[0].run;
    }

    unsigned int keyboardJump1() const
    {
        return players[0].jump;
    }

    unsigned int keyboardDrop1() const
    {
        return players[0].dropitem;
    }

    unsigned int keyboardPause1() const
    {
        return players[0].pause;
    }

    unsigned int keyboardAltJump1() const
    {
        return players[0].altjump;
    }

    unsigned int keyboardAltRun1() const
    {
        return players[0].altrun;
    }

    unsigned int joystickJump1() const
    {
        return players[0].j_jump;
    }

    unsigned int joystickRun1() const
    {
        return players[0].j_run;
    }

    unsigned int joystickDrop1() const
    {
        return players[0].j_dropitem;
    }

    unsigned int joystickPause1() const
    {
        return players[0].j_pause;
    }

    unsigned int joystickAltJump1() const
    {
        return players[0].j_altjump;
    }

    unsigned int joystickAltRun1() const
    {
        return players[0].j_altrun;
    }



    unsigned int controllerType2() const
    {
        return players[1].controllerType;
    }

    unsigned int keyboardUp2() const
    {
        return players[1].up;
    }

    unsigned int keyboardDown2() const
    {
        return players[1].down;
    }

    unsigned int keyboardLeft2() const
    {
        return players[1].left;
    }

    unsigned int keyboardRight2() const
    {
        return players[1].right;
    }

    unsigned int keyboardRun2() const
    {
        return players[1].run;
    }

    unsigned int keyboardJump2() const
    {
        return players[1].jump;
    }

    unsigned int keyboardDrop2() const
    {
        return players[1].dropitem;
    }

    unsigned int keyboardPause2() const
    {
        return players[1].pause;
    }

    unsigned int keyboardAltJump2() const
    {
        return players[1].altjump;
    }

    unsigned int keyboardAltRun2() const
    {
        return players[1].altrun;
    }

    unsigned int joystickRun2() const
    {
        return players[1].j_run;
    }

    unsigned int joystickJump2() const
    {
        return players[1].j_jump;
    }

    unsigned int joystickDrop2() const
    {
        return players[1].j_dropitem;
    }

    unsigned int joystickPause2() const
    {
        return players[1].j_pause;
    }

    unsigned int joystickAltJump2() const
    {
        return players[1].j_altjump;
    }

    unsigned int joystickAltRun2() const
    {
        return players[1].j_altrun;
    }

public slots:
    bool read();
    bool write();
    void setFullscreen(bool fullscreen)
    {
        m_data.fullScreen = fullscreen;
        emit fullscreenUpdated();
    }

    void setControllerType1(unsigned int controllerType1)
    {
        players[0].controllerType = controllerType1;
        emit controllerType1Updated();
    }

    void setKeyboardUp1(unsigned int keyboardUp1)
    {
        players[0].up = keyboardUp1;
        emit keyboardUp1Updated();
    }

    void setKeyboardDown1(unsigned int keyboardDown1)
    {
        players[0].down = keyboardDown1;
        emit keyboardDown1Updated();
    }

    void setKeyboardLeft1(unsigned int keyboardLeft1)
    {
        players[0].left = keyboardLeft1;
        emit keyboardLeft1Updated();
    }

    void setKeyboardRight1(unsigned int keyboardRight1)
    {
        players[0].right = keyboardRight1;
        emit keyboardRight1Updated();
    }

    void setKeyboardRun1(unsigned int keyboardRun1)
    {
        players[0].run = keyboardRun1;
        emit keyboardRun1Updated();
    }

    void setKeyboardJump1(unsigned int keyboardJump1)
    {
        players[0].jump = keyboardJump1;
        emit keyboardJump1Updated();
    }

    void setKeyboardDrop1(unsigned int keyboardDrop1)
    {
        players[0].dropitem = keyboardDrop1;
        emit keyboardDrop1Updated();
    }

    void setKeyboardPause1(unsigned int keyboardPause1)
    {
        players[0].pause = keyboardPause1;
        emit keyboardPause1Updated();
    }

    void setKeyboardAltJump1(unsigned int keyboardAltJump1)
    {
        players[0].altjump = keyboardAltJump1;
        emit keyboardAltJump1Updated();
    }

    void setKeyboardAltRun1(unsigned int keyboardAltRun1)
    {
        players[0].altrun = keyboardAltRun1;
        emit keyboardAltRun1Updated();
    }

    void setJoystickRun1(unsigned int joystickRun1)
    {
        players[0].j_run = joystickRun1;
        emit joystickRun1Updated();
    }

    void setJoystickJump1(unsigned int joystickJump1)
    {
        players[0].j_jump = joystickJump1;
        emit joystickJump1Updated();
    }

    void setJoystickDrop1(unsigned int joystickDrop1)
    {
        players[0].j_dropitem = joystickDrop1;
        emit joystickDrop1Updated();
    }

    void setJoystickPause1(unsigned int joystickPause1)
    {
        players[0].j_pause = joystickPause1;
        emit joystickPause1Updated();
    }

    void setJoystickAltJump1(unsigned int joystickAltJump1)
    {
        players[0].j_altjump = joystickAltJump1;
        emit joystickAltJump1Updated();
    }

    void setJoystickAltRun1(unsigned int joystickAltRun1)
    {
        players[0].j_altrun = joystickAltRun1;
        emit joystickAltRun1Updated();
    }



    void setControllerType2(unsigned int controllerType2)
    {
        players[1].controllerType = controllerType2;
        emit controllerType2Updated();
    }

    void setKeyboardUp2(unsigned int keyboardUp2)
    {
        players[1].up = keyboardUp2;
        emit keyboardUp2Updated();
    }

    void setKeyboardDown2(unsigned int keyboardDown2)
    {
        players[1].down = keyboardDown2;
        emit keyboardDown2Updated();
    }

    void setKeyboardLeft2(unsigned int keyboardLeft2)
    {
        players[1].left = keyboardLeft2;
        emit keyboardLeft2Updated();
    }

    void setKeyboardRight2(unsigned int keyboardRight2)
    {
        players[1].right = keyboardRight2;
        emit keyboardRight2Updated();
    }

    void setKeyboardRun2(unsigned int keyboardRun2)
    {
        players[1].run = keyboardRun2;
        emit keyboardRun2Updated();
    }

    void setKeyboardJump2(unsigned int keyboardJump2)
    {
        players[1].jump = keyboardJump2;
        emit keyboardJump2Updated();
    }

    void setKeyboardDrop2(unsigned int keyboardDrop2)
    {
        players[1].dropitem = keyboardDrop2;
        emit keyboardDrop2Updated();
    }

    void setKeyboardPause2(unsigned int keyboardPause2)
    {
        players[1].pause = keyboardPause2;
        emit keyboardPause2Updated();
    }

    void setKeyboardAltJump2(unsigned int keyboardAltJump2)
    {
        players[1].altjump = keyboardAltJump2;
        emit keyboardAltJump2Updated();
    }

    void setKeyboardAltRun2(unsigned int keyboardAltRun2)
    {
        players[1].altrun = keyboardAltRun2;
        emit keyboardAltRun2Updated();
    }

    void setJoystickRun2(unsigned int joystickRun2)
    {
        players[1].j_run = joystickRun2;
        emit joystickRun2Updated();
    }

    void setJoystickJump2(unsigned int joystickJump2)
    {
        players[1].j_jump = joystickJump2;
        emit joystickJump2Updated();
    }

    void setJoystickDrop2(unsigned int joystickDrop2)
    {
        players[1].j_dropitem = joystickDrop2;
        emit joystickDrop2Updated();
    }

    void setJoystickPause2(unsigned int joystickPause2)
    {
        players[1].j_pause = joystickPause2;
        emit joystickPause2Updated();
    }

    void setJoystickAltJump2(unsigned int joystickAltJump2)
    {
        players[1].j_altjump = joystickAltJump2;
        emit joystickAltJump2Updated();
    }

    void setJoystickAltRun2(unsigned int joystickAltRun2)
    {
        players[1].j_altrun = joystickAltRun2;
        emit joystickAltRun2Updated();
    }


signals:
    void fullscreenUpdated();
    void controllerType1Updated();
    void keyboardUp1Updated();
    void keyboardDown1Updated();
    void keyboardLeft1Updated();
    void keyboardRight1Updated();
    void keyboardRun1Updated();
    void keyboardJump1Updated();
    void keyboardDrop1Updated();
    void keyboardPause1Updated();
    void keyboardAltJump1Updated();
    void keyboardAltRun1Updated();
    void joystickRun1Updated();
    void joystickJump1Updated();
    void joystickDrop1Updated();
    void joystickPause1Updated();
    void joystickAltJump1Updated();
    void joystickAltRun1Updated();
    void controllerType2Updated();
    void keyboardUp2Updated();
    void keyboardDown2Updated();
    void keyboardLeft2Updated();
    void keyboardRight2Updated();
    void keyboardRun2Updated();
    void keyboardJump2Updated();
    void keyboardDrop2Updated();
    void keyboardPause2Updated();
    void keyboardAltJump2Updated();
    void keyboardAltRun2Updated();
    void joystickRun2Updated();
    void joystickJump2Updated();
    void joystickDrop2Updated();
    void joystickPause2Updated();
    void joystickAltJump2Updated();
    void joystickAltRun2Updated();

private:
    QString m_configFilename;
    SMBX64_ConfigFile m_data;
};

#endif // CONTROLCONFIG_H

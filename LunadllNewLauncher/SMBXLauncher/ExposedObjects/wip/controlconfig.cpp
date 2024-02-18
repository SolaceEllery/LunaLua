#include "controlconfig.h"

#include "IniProcessor/ini_processing.h"

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

playerInputs players[199];

static QString temp = qApp->applicationDirPath() + "/inputs.ini";
static QString m_configFilenameV2 = "inputs.ini";
std::string m_configFilenameAndPath = temp.toStdString();

ControlConfig::ControlConfig(QObject *parent) : ControlConfig("config.dat", parent)
{}

ControlConfig::ControlConfig(const QString &configFilename, QObject *parent) :
    QObject(parent),
    m_configFilename(configFilename)
{
    setDefaults();

    read();
}

void ControlConfig::setDefaults()
{
    for (int idx = 0; idx <= 199; idx++)
    {
        players[idx].Reset();
    }

    IniProcessing inputConfig(m_configFilenameAndPath.c_str());
    for(int i = 0; i <= 199; i++)
    {
        inputConfig.beginGroup("Player " + std::to_string(i + 1) + " Controls");
        
        inputConfig.setValue("keyboard_up", players[i].up);
        inputConfig.setValue("keyboard_down", players[i].down);
        inputConfig.setValue("keyboard_left", players[i].left);
        inputConfig.setValue("keyboard_right", players[i].right);
        inputConfig.setValue("keyboard_jump", players[i].jump);
        inputConfig.setValue("keyboard_run", players[i].run);
        inputConfig.setValue("keyboard_dropitem", players[i].dropitem);
        inputConfig.setValue("keyboard_pause", players[i].pause);
        inputConfig.setValue("keyboard_altjump", players[i].altjump);
        inputConfig.setValue("keyboard_altrun", players[i].altrun);
        inputConfig.setValue("keyboard_special", players[i].special);
        inputConfig.setValue("keyboard_leftTrigger", players[i].leftTrigger);
        inputConfig.setValue("keyboard_rightTrigger", players[i].rightTrigger);

        inputConfig.setValue("controller_jump", players[i].j_jump);
        inputConfig.setValue("controller_run", players[i].j_run);
        inputConfig.setValue("controller_dropitem", players[i].j_dropitem);
        inputConfig.setValue("controller_pause", players[i].j_pause);
        inputConfig.setValue("controller_altjump", players[i].j_altjump);
        inputConfig.setValue("controller_altrun", players[i].j_altrun);

        inputConfig.setValue("controller_inputType", players[i].controllerType);
    }

    inputConfig.writeIniFile();
    inputConfig.close();
    
    m_data.players.clear();
    m_data.meta.ReadFileValid = true;
    m_data.fullScreen = false;

    for (int idx = 0; idx < 2; idx++)
    {
        m_data.players.push_back(SMBX64_ConfigPlayer());
        SMBX64_ConfigPlayer& plCfg = m_data.players[idx];
        plCfg.controllerType = 0;
        plCfg.k_up      = 38;
        plCfg.k_down    = 40;
        plCfg.k_left    = 37;
        plCfg.k_right   = 39;
        plCfg.k_run     = 90;
        plCfg.k_jump    = 88;
        plCfg.k_drop    = 16;
        plCfg.k_pause   = 27;
        plCfg.k_altjump = 65;
        plCfg.k_altrun  = 83;
        plCfg.j_run     = 2;
        plCfg.j_jump    = 0;
        plCfg.j_drop    = 6;
        plCfg.j_pause   = 7;
        plCfg.j_altjump = 1;
        plCfg.j_altrun  = 3;
        plCfg.id = static_cast<unsigned int>(idx + 1);
    }
}

bool ControlConfig::read()
{
    if (!QFile::exists(m_configFilenameV2))
    {
        setDefaults();
        //Can't open file to read... but let's return true anyway because we set
        //defaults and that'll be fine to use.
        return true;
    }

    FileFormats::ReadSMBX64ConfigFileF(m_configFilename, m_data);
    IniProcessing inputConfig(m_configFilenameAndPath.c_str());
    for(int i = 0; i <= 199; i++)
    {
        if(inputConfig.beginGroup("Player " + std::to_string(i + 1) + " Controls"))
        {
            players[i].up = inputConfig.value("keyboard_up", 38).toInt();
            players[i].down = inputConfig.value("keyboard_down", 40).toInt();
            players[i].left = inputConfig.value("keyboard_left", 37).toInt();
            players[i].right = inputConfig.value("keyboard_right", 39).toInt();
            players[i].jump = inputConfig.value("keyboard_jump", 88).toInt();
            players[i].run = inputConfig.value("keyboard_run", 90).toInt();
            players[i].dropitem = inputConfig.value("keyboard_dropitem", 16).toInt();
            players[i].pause = inputConfig.value("keyboard_pause", 27).toInt();
            players[i].altjump = inputConfig.value("keyboard_altjump", 65).toInt();
            players[i].altrun = inputConfig.value("keyboard_altrun", 83).toInt();
            players[i].special = inputConfig.value("keyboard_special", 68).toInt();
            players[i].leftTrigger = inputConfig.value("keyboard_leftTrigger", 81).toInt();
            players[i].rightTrigger = inputConfig.value("keyboard_rightTrigger", 87).toInt();
            
            players[i].j_jump = inputConfig.value("keyboard_jump", 0).toInt();
            players[i].j_run = inputConfig.value("keyboard_run", 2).toInt();
            players[i].j_dropitem = inputConfig.value("keyboard_dropitem", 6).toInt();
            players[i].j_pause = inputConfig.value("keyboard_pause", 7).toInt();
            players[i].j_altjump = inputConfig.value("keyboard_altjump", 1).toInt();
            players[i].j_altrun = inputConfig.value("keyboard_altrun", 3).toInt();
            
            players[i].controllerType = inputConfig.value("controller_inputType", i + 1).toInt();
        }
    }

    inputConfig.close();

    emit controllerType1Updated();
    emit keyboardUp1Updated();
    emit keyboardDown1Updated();
    emit keyboardLeft1Updated();
    emit keyboardRight1Updated();
    emit keyboardRun1Updated();
    emit keyboardJump1Updated();
    emit keyboardDrop1Updated();
    emit keyboardPause1Updated();
    emit keyboardAltJump1Updated();
    emit keyboardAltRun1Updated();
    emit joystickRun1Updated();
    emit joystickJump1Updated();
    emit joystickDrop1Updated();
    emit joystickPause1Updated();
    emit joystickAltJump1Updated();
    emit joystickAltRun1Updated();
    emit controllerType2Updated();
    emit keyboardUp2Updated();
    emit keyboardDown2Updated();
    emit keyboardLeft2Updated();
    emit keyboardRight2Updated();
    emit keyboardRun2Updated();
    emit keyboardJump2Updated();
    emit keyboardDrop2Updated();
    emit keyboardPause2Updated();
    emit keyboardAltJump2Updated();
    emit keyboardAltRun2Updated();
    emit joystickRun2Updated();
    emit joystickJump2Updated();
    emit joystickDrop2Updated();
    emit joystickPause2Updated();
    emit joystickAltJump2Updated();
    emit joystickAltRun2Updated();

    return true;
}

bool ControlConfig::write()
{
    //Write file
    unsigned int file_format = 64; //Target SMBX build
    FileFormats::WriteSMBX64ConfigFileF(m_configFilename, m_data, file_format);

    IniProcessing inputConfig(m_configFilenameAndPath.c_str());
    for(int i = 0; i <= 199; i++)
    {
        inputConfig.beginGroup("Player " + std::to_string(i + 1) + " Controls");
        
        inputConfig.setValue("keyboard_up", players[i].up);
        inputConfig.setValue("keyboard_down", players[i].down);
        inputConfig.setValue("keyboard_left", players[i].left);
        inputConfig.setValue("keyboard_right", players[i].right);
        inputConfig.setValue("keyboard_jump", players[i].jump);
        inputConfig.setValue("keyboard_run", players[i].run);
        inputConfig.setValue("keyboard_dropitem", players[i].dropitem);
        inputConfig.setValue("keyboard_pause", players[i].pause);
        inputConfig.setValue("keyboard_altjump", players[i].altjump);
        inputConfig.setValue("keyboard_altrun", players[i].altrun);
        inputConfig.setValue("keyboard_special", players[i].special);
        inputConfig.setValue("keyboard_leftTrigger", players[i].leftTrigger);
        inputConfig.setValue("keyboard_rightTrigger", players[i].rightTrigger);

        inputConfig.setValue("controller_jump", players[i].j_jump);
        inputConfig.setValue("controller_run", players[i].j_run);
        inputConfig.setValue("controller_dropitem", players[i].j_dropitem);
        inputConfig.setValue("controller_pause", players[i].j_pause);
        inputConfig.setValue("controller_altjump", players[i].j_altjump);
        inputConfig.setValue("controller_altrun", players[i].j_altrun);

        inputConfig.setValue("controller_inputType", players[i].controllerType);
    }

    inputConfig.writeIniFile();
    inputConfig.close();
    
    return true;
}

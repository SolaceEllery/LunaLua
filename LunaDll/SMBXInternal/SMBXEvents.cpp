#include "SMBXEvents.h"

bool EventHasTriggered[254] = {false};
bool EventSetToCancel[254] = {false};

// GET
SMBXEvent* SMBXEvents::Get(int index) {
    return SMBXEvent::Get(index);
}

// GET BY NAME
SMBXEvent* SMBXEvents::GetByName(std::wstring Name) {	
    SMBXEvent* pEventBase = (SMBXEvent*)GM_EVENTS_PTR;

    for(int i = 0; i < 255; i++) {
        if(pEventBase[i].pName == Name)
            return &(pEventBase[i]);
    }
    return 0;
}

int SMBXEvents::GetNumberFromName(std::wstring Name)
{	
    SMBXEvent* pEventBase = (SMBXEvent*)GM_EVENTS_PTR;

    for(int i = 0; i < 255; i++)
    {
        if(pEventBase[i].pName == Name)
            return i;
    }
    return 0;
}	

void SMBXEvents::TriggerEvent(int Index, int UnknownArg) {
}

void SMBXEvents::TriggerEvent(std::wstring str, short forceNoSmoke) {
    VB6StrPtr eventName(str);
    native_triggerEvent(&eventName, &forceNoSmoke);
    EventHasTriggered[SMBXEvents::GetNumberFromName(str)] = true;
}

bool SMBXEvents::EventWasTriggered(std::wstring eventName)
{
    if(EventHasTriggered[SMBXEvents::GetNumberFromName(eventName)])
    {
        return true;
    }
    return false;
}

void SMBXEvents::UpdateEventTriggers()
{
    for(int i = 0; i <= 254; i++)
    {
        if(EventHasTriggered[i])
        {
            EventHasTriggered[i] = false;
        }
    }
}

void SMBXEvents::CancelNewEvent(std::wstring str)
{
    int eventID = SMBXEvents::GetNumberFromName(str);
    EventSetToCancel[eventID] = true;
}

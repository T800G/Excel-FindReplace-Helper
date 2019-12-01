#ifndef _EVENTS_75D0CC67_0F38_4255_9DF5_F7D49E4BFE24_
#define _EVENTS_75D0CC67_0F38_4255_9DF5_F7D49E4BFE24_

#ifdef _DEBUG
#define DBGTRACEEVENT(x) OutputDebugString(DbgGetWinEventName((x)))

LPCSTR DbgGetWinEventName(DWORD dwEvent)
{
	switch(dwEvent)
	{
		//https://msdn.microsoft.com/en-us/library/windows/desktop/dd318066(v=vs.85).aspx

		//case EVENT_SYSTEM_SWITCHSTART: return "EVENT_SYSTEM_SWITCHSTART";
		//case EVENT_SYSTEM_SWITCHEND: return "EVENT_SYSTEM_SWITCHEND";
		//case EVENT_SYSTEM_SOUND: return "EVENT_SYSTEM_SOUND";
		//case EVENT_SYSTEM_SCROLLINGSTART: return "EVENT_SYSTEM_SCROLLINGSTART";
		//case EVENT_SYSTEM_SCROLLINGEND: return "EVENT_SYSTEM_SCROLLINGEND";
		case EVENT_SYSTEM_MOVESIZESTART: return "EVENT_SYSTEM_MOVESIZESTART";
		case EVENT_SYSTEM_MOVESIZEEND: return "EVENT_SYSTEM_MOVESIZEEND";
		//case EVENT_SYSTEM_MINIMIZESTART: return "EVENT_SYSTEM_MINIMIZESTART";
		//case EVENT_SYSTEM_MINIMIZEEND: return "EVENT_SYSTEM_MINIMIZEEND";
		//case EVENT_SYSTEM_MENUSTART: return "EVENT_SYSTEM_MENUSTART";
		//case EVENT_SYSTEM_MENUPOPUPSTART: return "EVENT_SYSTEM_MENUPOPUPSTART";
		//case EVENT_SYSTEM_MENUPOPUPEND: return "EVENT_SYSTEM_MENUPOPUPEND";
		//case EVENT_SYSTEM_MENUEND: return "EVENT_SYSTEM_MENUEND";
		case EVENT_SYSTEM_FOREGROUND: return "EVENT_SYSTEM_FOREGROUND";
		////case EVENT_SYSTEM_END: return "EVENT_SYSTEM_END";
		//case EVENT_SYSTEM_DRAGDROPSTART: return "EVENT_SYSTEM_DRAGDROPSTART";
		//case EVENT_SYSTEM_DRAGDROPEND: return "EVENT_SYSTEM_DRAGDROPEND";
		//case EVENT_SYSTEM_DIALOGSTART: return "EVENT_SYSTEM_DIALOGSTART";
		//case EVENT_SYSTEM_DIALOGEND: return "EVENT_SYSTEM_DIALOGEND";
		////case EVENT_SYSTEM_DESKTOPSWITCH: return "EVENT_SYSTEM_DESKTOPSWITCH";
		//case EVENT_SYSTEM_CONTEXTHELPSTART: return "EVENT_SYSTEM_CONTEXTHELPSTART";
		//case EVENT_SYSTEM_CONTEXTHELPEND: return "EVENT_SYSTEM_CONTEXTHELPEND";
		//case EVENT_SYSTEM_CAPTURESTART: return "EVENT_SYSTEM_CAPTURESTART";
		//case EVENT_SYSTEM_CAPTUREEND: return "EVENT_SYSTEM_CAPTUREEND";
		////case EVENT_SYSTEM_ARRANGMENTPREVIEW: return "EVENT_SYSTEM_ARRANGMENTPREVIEW";
		//case EVENT_SYSTEM_ALERT: return "EVENT_SYSTEM_ALERT";
		//case EVENT_OBJECT_VALUECHANGE: return "EVENT_OBJECT_VALUECHANGE";
		//////case EVENT_OBJECT_UNCLOAKED: return "EVENT_OBJECT_UNCLOAKED";
		////case EVENT_OBJECT_TEXTSELECTIONCHANGED: return "EVENT_OBJECT_TEXTSELECTIONCHANGED";
		//////case EVENT_OBJECT_TEXTEDIT_CONVERSIONTARGETCHANGED: return "EVENT_OBJECT_TEXTEDIT_CONVERSIONTARGETCHANGED";
		//case EVENT_OBJECT_STATECHANGE: return "EVENT_OBJECT_STATECHANGE";
		case EVENT_OBJECT_SHOW: return "EVENT_OBJECT_SHOW";
		//case EVENT_OBJECT_SELECTIONWITHIN: return "EVENT_OBJECT_SELECTIONWITHIN";
		//case EVENT_OBJECT_SELECTIONREMOVE: return "EVENT_OBJECT_SELECTIONREMOVE";
		//case EVENT_OBJECT_SELECTIONADD: return "EVENT_OBJECT_SELECTIONADD";
		//case EVENT_OBJECT_SELECTION: return "EVENT_OBJECT_SELECTION";
		//case EVENT_OBJECT_REORDER: return "EVENT_OBJECT_REORDER";
		//case EVENT_OBJECT_PARENTCHANGE: return "EVENT_OBJECT_PARENTCHANGE";
		//case EVENT_OBJECT_NAMECHANGE: return "EVENT_OBJECT_NAMECHANGE";
		//case EVENT_OBJECT_LOCATIONCHANGE: return "EVENT_OBJECT_LOCATIONCHANGE";
		//////case EVENT_OBJECT_LIVEREGIONCHANGED: return "EVENT_OBJECT_LIVEREGIONCHANGED";
		////case EVENT_OBJECT_INVOKED: return "EVENT_OBJECT_INVOKED";
		//////case EVENT_OBJECT_IME_SHOW: return "EVENT_OBJECT_IME_SHOW";
		//////case EVENT_OBJECT_IME_HIDE: return "EVENT_OBJECT_IME_HIDE";
		//////case EVENT_OBJECT_IME_CHANGE: return "EVENT_OBJECT_IME_CHANGE";
		//////case EVENT_OBJECT_HOSTEDOBJECTSINVALIDATED: return "EVENT_OBJECT_HOSTEDOBJECTSINVALIDATED";
		case EVENT_OBJECT_HIDE: return "EVENT_OBJECT_HIDE";
		//case EVENT_OBJECT_HELPCHANGE: return "EVENT_OBJECT_HELPCHANGE";
		//case EVENT_OBJECT_FOCUS: return "EVENT_OBJECT_FOCUS";
		////case EVENT_OBJECT_END: return "EVENT_OBJECT_END";
		//////case EVENT_OBJECT_DRAGSTART: return "EVENT_OBJECT_DRAGSTART";
		//////case EVENT_OBJECT_DRAGLEAVE: return "EVENT_OBJECT_DRAGLEAVE";
		//////case EVENT_OBJECT_DRAGENTER: return "EVENT_OBJECT_DRAGENTER";
		//////case EVENT_OBJECT_DRAGDROPPED: return "EVENT_OBJECT_DRAGDROPPED";
		//////case EVENT_OBJECT_DRAGCOMPLETE: return "EVENT_OBJECT_DRAGCOMPLETE";
		//////case EVENT_OBJECT_DRAGCANCEL: return "EVENT_OBJECT_DRAGCANCEL";
		case EVENT_OBJECT_DESTROY: return "EVENT_OBJECT_DESTROY";
		//case EVENT_OBJECT_DESCRIPTIONCHANGE: return "EVENT_OBJECT_DESCRIPTIONCHANGE";
		//case EVENT_OBJECT_DEFACTIONCHANGE: return "EVENT_OBJECT_DEFACTIONCHANGE";
		case EVENT_OBJECT_CREATE: return "EVENT_OBJECT_CREATE";
		////case EVENT_OBJECT_CONTENTSCROLLED: return "EVENT_OBJECT_CONTENTSCROLLED";
		//////case EVENT_OBJECT_CLOAKED: return "EVENT_OBJECT_CLOAKED";
		//case EVENT_OBJECT_ACCELERATORCHANGE: return "EVENT_OBJECT_ACCELERATORCHANGE";
		////case EVENT_OEM_DEFINED_START: return "EVENT_OEM_DEFINED_START";
		////case EVENT_OEM_DEFINED_END: return "EVENT_OEM_DEFINED_END";
		//default: return ;
    }
return NULL;
}

#else
#define DBGTRACEEVENT(x)
#endif

#endif//_EVENTS_75D0CC67_0F38_4255_9DF5_F7D49E4BFE24_
#include "utils.h"

int keyboard() {
	Event e;
	do {
		getEvent(0,e);
        if(e.type==EVT_KEY_ON)
			return e.key;
    } while(e.type!=EVT_NONE);
	return 0;
}

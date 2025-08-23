#pragma once

bool Dummytoggle1 = false;
bool Dummytoggle2 = false;
bool Dummytoggle3 = false;
bool Dummytoggle4 = false;
bool Dummytoggle5 = false;
bool Dummytoggle6 = false;
bool Dummytoggle7 = false;
bool Dummytoggle8 = false;
bool Dummytoggle9 = false;
bool Dummytoggle10 = false;
bool Dummytoggle11 = false;
bool Dummytoggle12 = false;
bool Dummytoggle13 = false;
bool Dummytoggle14 = false;
bool Dummytoggle15 = false;
bool Dummytoggle16 = false;
bool Dummytoggle17 = false;
bool Dummytoggle18 = false;
bool Dummytoggle19 = false;
bool Dummytoggle20 = false;


// Place youe hooks here ....let me show an example of hook



bool IsIntExample2 = false; // this is our toggle 
// Int Method Offset Hooking Example:
int (*old_IntExample2)(void *instance);
int IntExample2(void *instance) {
	if (instance != NULL) {
		if (IsIntExample2) {
			return 7777; // add your custom value
		}
	}
	return old_IntExample2(instance);
}
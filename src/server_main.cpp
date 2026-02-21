#include "ChatServer.h"

#define PORT "3490"

using namespace std;

int main()
{
	ChatServer chat(PORT);
	chat.run();

	return 0;
}

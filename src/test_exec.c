#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <pidof.h>

char *server="this";
char *notfile ="this";
char *process[256];
int main(int argc, char* argv[])
{
	pid_t pid = 0;
	const char* command = "bash";
	printf("Forking");
	
	setuid(1000);	
	//pid = fork();
	
	//printf("fork pid %d\n",pid);
	if ( pid < 0 ) perror("This is error");
	
	else if ( pid == 0 ){	
		execlp(command,"bash","-c","/usr/bin/emacs");
		printf("Emacs pid %d\n",get_pidof("bash -c /usr/bin/emacs"));
		exit(0);
	}
	else if ( pid > 0 );
	return 0;
		
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	int c;
	char* uvalue = NULL;
	char* ivalue = NULL;
	char* dvalue = NULL;
	char* gvalue = NULL;
	char* avalue = NULL;
	int option = 0;
	struct passwd *pw;
	struct group *gr;

   static struct option long_options[]=
    {
        {"username",	 required_argument,	   0, 'u'},  
        {"useruid",	 required_argument,	   0, 'i'}, 
        {"groupname",	 required_argument,	   0, 'g'}, 
        {"groupuid",	 required_argument,	   0, 'd'}, 
        {"allgroups",	 no_argument,	   0, 's'}, 
        {"allinfo",	 required_argument,	   0, 'a'}, 
        {"bactive",	 no_argument,	   0, 'b'}, 
        {"help",	 no_argument,	   0, 'h'}, 
  		{0, 0, 0, 0}
 	};

    while((c=getopt_long(argc,argv,"u:i:g:d:sa:bh",long_options, &option_index))!=-1){
    {
    	if(c == -1)
    		break;
    	switch(c)
    	{
    		case 'h':
    			break;

    		case 'u':
    			value = optarg;
    			if((pw = getpwnam(value)) == NULL)
    			{
    				fprintf(stderr, "Get of user information failed\n" );
    				exit(-1);
    			}

        		printf("Nombre: %s\n", pw->pw_gecos);
				printf("Login: %s\n", pw->pw_name);
				printf("Password: %s\n", pw->pw_passwd);
				printf("UID: %d\n", pw->pw_uid);
				printf("Home: %s\n", pw->pw_dir);
				printf("Número de grupo principal: %d\n", pw->pw_gid);
				break;

			case 'i':
				value = optarg;
				if((pw = getpwuid(value)) == NULL)
				{
					fprintf(stderr, "Get of user information failed\n");
					exit(-1);
				}
       			printf("Nombre: %s\n", pw->pw_gecos);
				printf("Login: %s\n", pw->pw_name);
				printf("Password: %s\n", pw->pw_passwd);
				printf("UID: %d\n", pw->pw_uid);
				printf("Home: %s\n", pw->pw_dir);
				printf("Número de grupo principal: %d\n", pw->pw_gid);
				break;

			case 'a':
				value = optarg;
    			if((pw = getpwnam(value)) == NULL)
    			{
    				fprintf(stderr, "Get of user information failed\n" );
    				exit(-1);
    			}
        		printf("Nombre: %s\n", pw->pw_gecos);
				printf("Login: %s\n", pw->pw_name);
				printf("Password: %s\n", pw->pw_passwd);
				printf("UID: %d\n", pw->pw_uid);
				printf("Home: %s\n", pw->pw_dir);
				printf("Número de grupo principal: %d\n", pw->pw_gid);
				
				if((gr = getgrgid(pq->pw_gid)) == NULL)
				{
					fprintf(stderr, "Get of user information failed\n");
					exit(-1);
				}
          		printf("ID del grupo:%d Nombre del grupo: %s\n",gr->gr_gid, gr->gr_name);		
          		break;

          	case 's':
          		while(gr = getgrent())
          		{
          			printf("ID:%d Nombre del grupo:%s\n",gr->gr_gid,gr->gr_name);
          		}
          		break;

          	case 'b':
          		if((gr = getgrgid(getegid())) == NULL)
          		{
          			fprintf(stderr, "Get of group information failed\n", );
          			exit(-1);
          		}
      			printf("ID:%d Nombre del grupo: %s\n",gr->gr_gid, gr->gr_name);
      			break;
      		case '?':
      			break;

      		default:
      			abort();           		
    	}
    }

}
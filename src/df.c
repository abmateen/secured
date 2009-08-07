#include <stdio.h>
#include <sys/types.h>
#include <sys/vfs.h>
#include <errno.h>
#include <mntent.h>
#include <stdlib.h>
#include <unistd.h>
#include "df.h"
#include <stdlib.h>

void do_statfs( const struct mntent *fs );
void print_mount(const struct mntent *fs );

/* Variables in config file */
extern char *mailprogram;
extern char *server;
extern char *mailparamters;
extern char *notfile;

FILE* notf_file;
void generate_disk_report()
{
	
	// let me get mnt first
	FILE* fp;
	struct mntent *fs;
	notf_file = fopen(notfile,"w");
	fp = setmntent("/etc/mtab","r");
	
	if ( fp == NULL ){
		fprintf(stderr,": could not open: %s\n",strerror(errno));
		exit(1);


	}
			
	while ( (fs = getmntent(fp)) != NULL )
		do_statfs(fs);//print_mount(fs);
		
	endmntent(fp);
	fclose(notf_file);       


}
void print_mount( const struct mntent *fs)
{
	printf (" %s \n", fs->mnt_dir);
}

void do_statfs( const struct mntent *fs )
{
	struct statfs vfs;
	char *status;
	char pfree[100];

	int percent_free = 0;
	
	
	

	if ( notf_file == NULL ){
		perror("Error");
	    
	}

	if ( fs->mnt_fsname[0] != '/')
		return;
	
	if ( statfs(fs->mnt_dir, &vfs) != 0){
		fprintf(stderr,"%s error is ",strerror(errno));
		return;
	}
	
	/* Calculating percent free space */
	percent_free = (((double)((double)vfs.f_bavail / (double)vfs.f_blocks)) * (float)100.00);
	//sprintf(pfree,"%d", percent_free);
	//printf("%s\n",pfree);
      
	if ( percent_free < 10 && percent_free > 0 ){
	
	  status = "Critical" ;
	  fprintf(notf_file,"\n\n\n");
	  fprintf(notf_file,"Server:\t%s\n\n",server);
	  fprintf(notf_file,"FileSystem:\t%s\n\n", fs->mnt_fsname);
	  fprintf(notf_file,"Mounted On:\t%s\n\n", fs->mnt_dir);
	  fprintf(notf_file,"Status:\t%s\n\n",status); 	
	  fprintf(notf_file,"Percent Free:%d%\n",percent_free);
	  
	}
	else
	  status = "Good";
	
	//fclose(notification_file);	
	//printf("FileSystem %s\n",fs->mnt_fsname);
	//printf("mount on %s\n",fs->mnt_dir);
	//printf("%ld Free Inode size\n", vfs.f_ffree);
	//printf("%ld Free Block Size\n", vfs.f_bfree);
	//printf("%ld Block Size \n",vfs.f_bsize);
	//printf("%ld f_avail \n", vfs.f_bavail); // total avaliable maen free
	//printf("%ld total blocks \n", vfs.f_blocks);
	//printf("%ld percent free ---- %s \n\n",percent_free,status);
	
}


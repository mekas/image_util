#include <stdio.h>
#include <stdlib.h> //malloc related
#include <glib.h>
#include <glib/gstdio.h>
#include "cstring.c"
#include <wand/magick_wand.h>

int main(int argc, char **argv){
	//define the path to image
	#define k 5	
	char *filedir[k]={"day1/","day2/","day3/","day4/","rahma/"};
	char *filedirout[k]={"day1_out/","day2_out/","day3_out/","day4_out/","rahma_out/"};
	//printf("%s\n",filedir);
	GDir *dir;
	GError *error;
	const gchar *filename;
	
	//setup imagemagick related variables
	MagickWand *m_wand = NULL;
	int width, height;
	
	char *imgname,*pathimgoutname,*pathimg;
	
	int i;
	for(i=0;i<k;i++){
		dir=g_dir_open(filedir[i],0,&error);
		//create output directory
		g_mkdir_with_parents(filedirout[i],0755);
		while((filename = g_dir_read_name(dir))){
			MagickWandGenesis();	
			m_wand = NewMagickWand();
			int dot_pos = charpos(filename, '.');
			//char *inputname = a
			imgname = getFilename(filename,dot_pos);
			pathimgoutname = appendString(filedirout[i],imgname);
			pathimg = appendString(filedir[i], (char *)filename);
			pathimgoutname=appendString(pathimgoutname,".jpg");		
			printf("%s\n",pathimg);				
			
			//read the image
			MagickReadImage(m_wand, pathimg);
			//get width and height
			width = MagickGetImageWidth(m_wand);
			height = MagickGetImageHeight(m_wand);
			printf("width:%d, height:%d \n",width, height);
			
			//cut them in half but make sure they don't underflow
			if((width/2)<1)
				width=1;
			else
				width/=2;
			if((height/2)<1)
				height=1;
			else
				height/=2;
			//resize the image using the lanczos filter
			//last parameter is the blur parameter
			MagickResizeImage(m_wand, width, height, LanczosFilter,1);
			
			//set the compression quality to 95 (high quality = low compression)
			MagickSetImageCompressionQuality(m_wand, 95);
			
			//write the new image
			MagickWriteImage(m_wand, pathimgoutname);
			// clean up
			if(m_wand)	
				m_wand = DestroyMagickWand(m_wand);
				
			MagickWandTerminus();
		}
	}
	
}

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

// function for copying the contents of one(text1) file to another(text2).
void copyFile (char text1[], char text2[]) { // text1 = fromfile; text2 --> toFile
  FILE *fp; // pointer for text1
  FILE *fn; // pointer for text2
  fp = fopen(text1, "r"); // in 'read' mode
  fn = fopen(text2, "w"); // in 'write' mode

  // Handling exceptions
  if (fp == NULL) {
    printf("ERROR. %s could not be opened.\n", text1);
    _exit;
  }
  else if (fn == NULL) {
     printf("ERROR. %s could not be opened.\n", text2);
     _exit;
  }

  // char pointer
  char pointer = fgetc(fp);

  while (pointer != EOF) {

    // type in text2 until pointer reaches End Of File.
    fprintf (fn, "%c", pointer);

    // retrieving the next character from text2.
    pointer = fgetc(fp);
  }
  fclose(fp);
  fclose(fn);
}

int main(int argc, char *argv[])
{
   // getting the Current Working Directory
   char cwd[200];
   getcwd(cwd, sizeof(cwd));

   // working directory formatting
   char slash = '/';
   char logfile[200];
   strcpy(logfile, cwd);
   strncat(logfile, &slash, 1);
   strcat(logfile, "logfile.txt");

   // declaring a pointer for logfile
   FILE *logp;

   // in the beginning of the execution of program, new file "logfile.txt is created"
   // in subsequent executions, the operations on textfiles are recorded in "logfile.txt" file.
   logp = fopen(logfile, "a");

   // Error handling
   if (argc == 1) {
      printf ("Cannot have a single argument\n");
   }

   if (argc == 2) {

     // displays the previous operations done on textfiles.
     if (strcmp(argv[1], "changelog")==0) {
       FILE *temp;

       // opening logfile in 'read' mode
       temp = fopen(logfile, "r");
       char point = getc(temp);
       while (point != EOF) {
         printf ("%c", point);
         point = getc(temp);
       }
     }

     // else-if is used to handle errors.
     else if (strcmp(argv[1], "fcreate") == 0) {
        printf ("Error. An argument is missing:\nfcreate <filename.txt>\n\n");
        return 0;
      }

     else if (strcmp(argv[1], "fdelete") == 0) {
        printf ("Error. An argument is missing:\nfdelete <filename.txt>\n\n");
        return 0;
      }

     else if (strcmp(argv[1], "fdisplay") == 0) {
        printf ("Error. An argument is missing:\nfdisplay <filename.txt>\n\n");
        return 0;
      }

    else if (strcmp(argv[1], "fappendline") == 0) {
        printf ("Error. An argument is missing:\nfappendline <filename.txt>\n\n");
        return 0;
    }

    else if (strcmp(argv[1], "nolines") == 0) {
        printf ("Error. An argument is missing:\nnolines <filename.txt>\n\n");
        return 0;
    }

    else if (strcmp(argv[1], "fcopy") == 0) {
        printf ("Error. Arguments are missing:\nfcopy <fromfile.txt> <tofile.txt>\n\n");
        return 0;
    }

    else if (strcmp(argv[1], "fdeleteline") == 0) {
        printf ("Error. Arguments are missing:\nfdeleteline <filename.txt> {line number}\n\n");
        return 0;
    }

    else if (strcmp(argv[1], "finsertline") == 0) {
        printf ("Error. Arguments are missing:\nfinsertline <filename.txt> {line number}\n\n");
        return 0;
    }

    else if (strcmp(argv[1], "fdeleteline") == 0) {
        printf ("Error. Arguments are missing:\nfdeleteline <filename.txt> {line number}\n\n");
        return 0;
    }

    else {
        printf("%s: Argument is not found\n ", argv[1]);
        return 0;
    }
    return 0;
   }


   FILE *fp;

   if (argc == 3) {

     // formatting the working directory of the file.
     char fullDirectory[200];
     char pointer;
     strcpy(fullDirectory, cwd);
     strncat(fullDirectory, &slash, 1);
     strcat(fullDirectory, argv[2]);

     // Handling error
     if (strcmp(argv[1], "changelog") == 0) {
       printf ("Too many arguments. The format: changelog.\n");
       return 0;
     }

     else if (strcmp(argv[1], "fcopy") == 0) {
         printf ("Error. An argument is missing:\nfcopy <fromfile.txt> <tofile.txt>\n\n");
         return 0;
     }

     else if (strcmp(argv[1], "fdeleteline") == 0) {
         printf ("Error. An argument is missing:\nfdeleteline <filename.txt> {line number}\n\n");
         return 0;
     }

     else if (strcmp(argv[1], "finsertline") == 0) {
         printf ("Error. An argument is missing:\nfinsertline <filename.txt> {line number}\n\n");
         return 0;
     }

     else if (strcmp(argv[1], "fdeleteline") == 0) {
         printf ("Error. An rgument is missing:\nfdeleteline <filename.txt> {line number}\n\n");
         return 0;
     }

     // creatting a new file
     else if (strcmp(argv[1], "fcreate") == 0) {
        fp = fopen(fullDirectory, "w");

        //recording the operations done on textfiles in logfile
        fputs(argv[0], logp);
        fprintf (logp, "%c", ' ');
        fputs(argv[1], logp);
     }

     // command for deleting the file.
     else if (strcmp(argv[1], "fdelete") == 0) {
        if (remove(fullDirectory) == 0)
          printf("File has been successfuly deleted\n");
        else
          printf ("File could not be deleted\n");

        // recording the operations done on textfiles in logfile
        fputs(argv[0], logp);
        fprintf (logp, "%s", " ");
        fputs(argv[1], logp);
        fprintf (logp, "%c", '\n');
     }

      // command to display the contents of the textfile
     else if (strcmp(argv[1], "fdisplay") == 0) {
        fp = fopen(fullDirectory, "r");
        pointer = fgetc(fp);
        while (pointer != EOF) {
          printf("%c", pointer);
          pointer = fgetc(fp);
        }

        // recording the operations done on the textfiles in logfile
        fputs(argv[0], logp);
        fprintf (logp, "%c", ' ');
        fputs(argv[1], logp);
        fprintf(logp, "%c", ' ');
        fputs(argv[2], logp);
        fprintf(logp, "%c", '\n');
     }

     // command to append lines
     else if (strcmp(argv[1], "fappendline") == 0) {

        // open the textfile in 'append' mode
        fp = fopen(fullDirectory, "a");
        char string[200];
        printf("Please, type your line to be appended:\n");
        fgets(string, 200 ,stdin);
        fputs(string, fp);

        // recording the operations done on the textfiles in logfiles.
        fputs(argv[0], logp);
        fprintf (logp, "%c", ' ');
        fputs(argv[1], logp);
        fprintf(logp, "%c", ' ');
        fputs(argv[2], logp);
        fprintf (logp, "%c", '\n');

     }
     // command to display number of lines of content in textfile.
     else if (strcmp(argv[1], "nolines") == 0) {
        int lines = 0;
        fp = fopen(fullDirectory, "r");
        do {
          pointer = fgetc(fp);
          // number of lines in textfiles is number of '\n' characters +1
          if (pointer == '\n') {
            pointer = fgetc(fp);
            // if the next line does not contain ' ' and EOF, then we incrment lines
            if (pointer != ' ' && pointer != EOF) lines ++;
          }
        } while (pointer != EOF);

        printf("There are %d lines.\n", lines+1);

        // recording the operations done on the textfiles in logfiles.
        fputs(argv[0], logp);
        fprintf (logp, "%c", ' ');
        fputs(argv[1], logp);
        fprintf(logp, "%c", ' ');
        fputs(argv[2], logp);
        fprintf (logp, "%c", '\n');
     }


     // (The addtional function I wrote) command to clear the text with specified name
     else if (strcmp(argv[1], "fclear") == 0) {
       fp = fopen (fullDirectory, "w");

       // recording the operations done on the textfiles in logfiles.
       fputs(argv[0], logp);
       fprintf (logp, "%s", " ");
       fputs(argv[1], logp);
       fprintf(logp, "%c", '\n');
     }

     fclose(fp);
   }

   if (argc == 4) {
     // command for concatentaing the contents of 2 textfiles.
        if (strcmp(argv[1], "fconcat") == 0) {
          char fromFile[200];
          char toFile[200];

          // directory formatting
          strcpy(fromFile, cwd);
          strncat(fromFile, &slash, 1);
          strcpy(fromFile, argv[2]);

          //direcory formatting
          strcpy(toFile, cwd);
          strncat(toFile, &slash, 1);
          strcpy(toFile, argv[3]);

          FILE *fp = fopen(fromFile, "r"); 'read' mode because we are reading from this text file
          FILE *fn = fopen(toFile, "a"); // 'append' mode because we appending from previous file


          int pointer = fgetc(fp);
          while (pointer != EOF) {
            fprintf(fn, "%c", pointer);
            pointer = fgetc(fp);
          }
          fclose(fp);
          fclose (fn);
        }

        else if (strcmp(argv[1], "fcopy") == 0) {
        char fromFile[200];
        char toFile[200];
        strcpy(fromFile, cwd);
        strncat(fromFile, &slash, 1);
        strcpy(fromFile, argv[2]);

        strcpy(toFile, cwd);
        strncat(toFile, &slash, 1);
        strcpy(toFile, argv[3]);


        copyFile (fromFile, toFile);

        // recording the operations done on the textfiles in logfiles.
        fputs(argv[0], logp);
        fprintf (logp, "%s", " ");
        fputs(argv[1], logp);
        fprintf (logp, "%s", " ");
        fputs(argv[2], logp);
        fprintf(logp, "%c", '\n');
      }

      // command for deleting a the content of specific line
      else if (strcmp(argv[1], "fdeleteline") == 0) {

         // direcory formatting. fromfile is the name of the oroginal file.
         char fromfile[200];
         strcpy(fromfile, cwd);
         strncat(fromfile, &slash, 1);
         strcat(fromfile, argv[2]);

        // direcory formatting. tempfile is the temporary file to store the
        // contents of the original file with 1 line deleted.
         char tempfile[200];
         strcpy(tempfile, cwd);
         strncat(tempfile, &slash, 1);
         strcat(tempfile, "tempfile.txt");

         // used to determine in which line the algorithm is pointing
         int count = 0;

         // opening the tempfile in 'write' mode
         FILE *fp = fopen(fromfile, "r");

         // opening the tempfile in 'write' mode
         FILE *fn = fopen(tempfile, "w");

         // error handling in case it could not be opened
         if (fp == NULL) {
           printf("ERROR. tempfile.txt could not be opened.\n");
           _exit;
         }

         // getting contents of the oroginal file element by element
         int pointer = fgetc(fp);

         while (pointer != EOF) {

            //used to trace which line the algorithm is pointing to.
            if (pointer == '\n')
              count ++;

            // so when the algorithm reaches the line to be deleted, it just
            // increments the pointer to point to the next element in that line
            // until it reaches '\n' character. By doing that the elements of
            // that line is not compied to tempfile.
            if ((count + 1) == atoi(argv[3])) {
               pointer = fgetc(fp);
               continue;
             }

          // inputting the contents of the original file with one line missing
          fprintf(fn, "%c", pointer);

          // incrementing the pointer
          pointer = fgetc(fp);
         }

         fclose(fn);
         fclose(fp);

         // copy the contents of the tempfile to original fromfile
         copyFile(tempfile, fromfile);

         // then delete the temporary file
         if (remove (tempfile) == 0) {
            printf ("The line %d has been successfuly deleted.\n", atoi(argv[3]));
         }

         // recording the operations done on the textfiles in logfiles.
         fputs(argv[0], logp);
         fprintf (logp, "%s", " ");
         fputs(argv[1], logp);
         fprintf (logp, "%s", " ");
         fputs(argv[2], logp);
         fprintf(logp, "%c", '\n');
      }

      // command to insert a line of content to the file
      else if (strcmp(argv[1], "finsertline") == 0) {
        // asking for the input line from stdin
         char text[200] = {};
         printf ("Please, insert a text:\n");
         fgets(text, 200, stdin);

         // direcory formatting of the original file
         char currentfile[200];
         strcpy(currentfile, cwd);
         strncat(currentfile, &slash, 1);
         strcat(currentfile, argv[2]);

         // directory formatting of the temporary file with new line
         char tempfile[200];
         strcpy(tempfile, cwd);
         strncat(tempfile, &slash, 1);
         strcat(tempfile, "tempfile.txt");

        // for tracing which line the algorithm is pointing to.
         int count = 0;
         int pointer;

         // opening the files and handling error
         FILE *fn;
         FILE *fp;
         fp = fopen (currentfile, "r");
         if (fp == NULL) {
           printf("ERROR. tempfile.txt could not be opened.\n");
           _exit;
         }
         fn = fopen (tempfile, "w");
         pointer = fgetc(fp);
         while (pointer != EOF) {

           // once the algorithms reaches spcified line, it uses fputs() function
           // to insert the line into temporary file. And increments count which
           // means the algorithm starts with the next line.
           if ((count + 1) == atoi(argv[3])) {
             fputs(text, fn);
             count ++;
           }

           // when pointer == '\n' we increment count, to keep track of which line
           // we are tracing.
           if (pointer == '\n') {
             count ++;
           }

           // inputting the characters into temporary file
           fprintf (fn, "%c", pointer);

           // incrementing the pointer so that it indicates to the the next
           // character
           pointer = fgetc(fp);
         }
         fclose (fp);
         fclose(fn);

         // copying the contents of the temporary file to original file
         copyFile(tempfile, currentfile);

         // recording the operations done on the textfiles in logfiles.
         fputs(argv[0], logp);
         fprintf (logp, "%s", " ");
         fputs(argv[1], logp);
         fprintf (logp, "%s", " ");
         fputs(argv[2], logp);
         fprintf(logp, "%c", '\n');
       }

      // command to display the contents of the specific line
       else if (strcmp(argv[1], "fdisplayline") == 0) {
          FILE *fp;
          char pointer;
          int count = 0;

          char currentfile[200];
          strcpy(currentfile, cwd);
          strncat(currentfile, &slash, 1);
          strcat(currentfile, argv[2]);

          fp = fopen (currentfile, "r");
          if (fp == NULL) {
            printf("ERROR. tempfile.txt could not be opened.\n");
            _exit;
          }
          // take each element for the file
          pointer = fgetc(fp);
          while (pointer != EOF) {
            //when the algorithms points to that specfic line print the characters
            if ((count +1) == atoi(argv[3])) {
              printf ("%c", pointer);
            }
            if (pointer == '\n') {
              count ++;
            }
            pointer = fgetc(fp);
          }
          fclose (fp);

          // recording the operations done on the textfiles in logfiles.
          fputs(argv[0], logp);
          fprintf (logp, "%s", " ");
          fputs(argv[1], logp);
          fprintf (logp, "%s", " ");
          fputs(argv[2], logp);
          fprintf(logp, "%c", '\n');
        }

        // headling errors.
        else if (strcmp(argv[1], "fcreate") == 0) {
           printf ("Error. Too many arguments are given:\nfcreate <filename.txt>\n\n");
           return 0;
         }

        else if (strcmp(argv[1], "fdelete") == 0) {
           printf ("Error. Too many arguments are given:\nfdelete <filename.txt>\n\n");
           return 0;
         }

        else if (strcmp(argv[1], "fdisplay") == 0) {
           printf ("Error. Too many arguments are given:\nfdisplay <filename.txt>\n\n");
           return 0;
         }

       else if (strcmp(argv[1], "fappendline") == 0) {
           printf ("Error. Too many arguments are given:\nfappendline <filename.txt>\n\n");
           return 0;
       }

       else if (strcmp(argv[1], "nolines") == 0) {
           printf ("Error. Too many arguments are given:\nnolines <filename.txt>\n\n");
           return 0;
       }

       else if (strcmp(argv[1], "fcopy") == 0) {
           printf ("Error. Too many arguments are given:\nfcopy <fromfile.txt> <tofile.txt>\n\n");
           return 0;
       }

       else {
           printf("%s: Argument is not found\n ", argv[1]);
           return 0;
       }
      }
   }

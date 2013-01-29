     #include <stdio.h>
     #include <stdlib.h>
     #include <getopt.h>
     
     /* Flag set by ‘--verbose’. */
     static int verbose_flag;
     
     int
     main (int argc, char **argv)
     {
       int c;
	   int i;
	   char *argument;

	   
       while (1)
         {
           static struct option long_options[] =
             {
               /* These options set a flag. */
               {"verbose", no_argument,       &verbose_flag, 1},
               /* These options don't set a flag.
                  We distinguish them by their indices. */
               {"add",     no_argument,       0, 'a'},
               {"append",  no_argument,       0, 'b'},
               {"aide",  no_argument,       0, 'h'},
               {"verb",  no_argument, 0, 'v'},
               {"delete",  required_argument, 0, 'd'},
               {"create",  required_argument, 0, 'c'},
               {"file",    required_argument, 0, 'f'},
               {0, 0, 0, 0}
             };
           /* getopt_long stores the option index here. */
           int option_index = 0;
     
           c = getopt_long (argc, argv, "abvhc:d:f:",
                            long_options, &option_index);
     
           /* Detect the end of the options. */
           if (c == -1)
             break;
		   
           switch (c)
             {
             case 0:
               /* If this option set a flag, do nothing else now. */
               if (long_options[option_index].flag != 0)
                 break;
               printf ("option %s", long_options[option_index].name);
               if (optarg)
                 printf (" with arg %s", optarg);
               printf ("\n");
               break;
     
             case 'a':
               puts ("option -a\n");
               break;
     
             case 'b':
               puts ("option -b\n");
               break;
     
             case 'c':
               printf ("option -c with value `%s'\n", optarg);
               break;
     
             case 'd':
               printf ("option -d with value `%s'\n", optarg);
               break;
     
             case 'f':
               printf ("option -f with value `%s'\n", optarg);
               break;
               
             case 'h':
				if(long_options[i].has_arg == 0)
					argument = "ne prend aucun argument";
				else
					argument = "un argument est requis";
					
				for(i = 0 ; i < 8 ; i++){
					char *valeur1 = (char)long_options[i].val;
					printf("Option : %s, %s,  valeur %s \n",long_options[i].name,argument,valeur1);	
				}
             break;
              
             case 'v':
				puts("option -v \n");
             break;
     
             case '?':
               /* getopt_long already printed an error message. */
               break;
     
             default:
               abort ();
             }
         }
          /* Instead of reporting ‘--verbose’
          and ‘--brief’ as they are encountered,
          we report the final status resulting from them. */
       if (verbose_flag)
         puts ("mode verbose activer");
     
       /* Print any remaining command line arguments (not options). */
       if (optind < argc)
         {
           printf ("Ceci n'est pas une option: ");
           while (optind < argc)
             printf ("%s ", argv[optind++]);
           putchar ('\n');
         }
     
       exit (0);
     }


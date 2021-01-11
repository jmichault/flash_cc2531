# gawk-skripto por traduki po-dosieron el esperanto al alia lingvo
# la ideo estas prilabori MSGIDojn por kiuj la MSGSTR estas malplena.
# MSGID-oj, kiuj havas Aferon inter layout, lang-ref, lang-niv, Fenced ne estas tradukitaj.
# Ni tiam eltranĉas la tradukenda tekston por forigi la elementojn de la sintakso ~ Markdown ~
# hiperligoj, kodblokoj kaj teksto kursivigita per "_" ne estas tradukitaj.
#
# google web translate konservas  «(°99°)».
# 
BEGIN {
#  MARK1="(zzz";
#  MARK2=")";
#  MARKEXPR= " *[（\\(] *[zZ]{2,3} *[0-9]+ *[）\\)] *";
#  if ( (dst == "bn") || (dst == "hi") || (dst == "ja") || (dst == "pa") || (dst == "zh") )
#  {
    MARK1="(°";
    MARK2="°)";
    MARKEXPR=" *[（\\(][ \\.。°0-9]*[°][ \\.。°0-9]*[）\\)] *";
#  }
}
{
  if ( CONTMSG==1 && substr($1,1,1) != "\"")
  { # fino de plurlinia mesaĝo
    CONTMSG=0;
  }
  if ($2 == "fuzzy")
  {
    FUZZY=1;
  }
  if ($1 == "msgid")
  {
    MSGID=substr($0,7);
    MSGSTR=substr($0,8,length($0)-8);
    MSGWRAP=0;
    if(MSGID=="\"\"")
    {
      CONTMSG=1;
      MSGWRAP=1;
    }
  }
  else if ( CONTMSG==1 && substr($1,1,1) == "\"")
  { # daŭrigo de plurlinia mesaĝo
    # enmemorigi MSGID-liniojn
    MSGID=MSGID "\n" $0;
    # enmemorigi netradukitan mesaĝon
    MSGSTR=MSGSTR substr($0,2,length($0)-2);
  }
  else if ($1 == "msgstr")
  {
    if( ($2 != "\"\"" && $2 != "\"\\n\"") || MSGID == "\"\"")
    { # mesaĝo jam tradukita
      print ("msgid " MSGID);
      print $0;
    }
    else
    {
      # msgstr "" kaj MSGID != ""
      $0="";
      getline
      if ( substr($1,1,1) == "\"")
      { # plurlinia mesaĝo jam tradukita
        print ("msgid " MSGID);
        printf("msgstr \"\"\n");
        print $0;
        FUZZY=0;
        MATTER="";
	next;
      }
      if(MATTER == "lang")
      {
        print ("msgid " MSGID);
        printf("msgstr \"" dst "\"\n");
      }
      else if(MATTER == "layout")
      {
        print ("msgid " MSGID);
        print ("msgstr " MSGID);
      }
      else if(MATTER == "lang-ref")
      {
        print ("msgid " MSGID);
        print ("msgstr " MSGID);
      }
      else if(MATTER == "lang-niv")
      {
        print ("msgid " MSGID);
        print ("msgstr \"auto\"" );
      }
      else if(MATTER == "Fenced")
      {
        print ("msgid " MSGID);
        print ("msgstr " MSGID);
      }
      else
      { # ĉi tiu mesaĝo estas tradukenda
        if(FUZZY ==0)
          print ("#, fuzzy");
        print ("msgid " MSGID);
        printf("msgstr \"");
	#  anstataŭigi markdown-etikedojn per markoj
        ##print ( "MSGSTR="MSGSTR);	##
        split(MSGSTR,MSGS,"^<a *id *=|</a>|^[ \t]*|[ \t]*\\\\\\\\.|[ \t]*\\\\.|[ \t]*!\\[[ \t]*|[ \t]*[_\\*`<>\\[\\]\\(\\)~]+[ \t]*",SEPS);
	MSG0 = "";
	MSGSLEN = length(MSGS);
        ##print ("MSGSLEN="MSGSLEN); ##
        ##for (x=0 ; x<=MSGSLEN ; x++)		##
	##	print ("MSGS "x " : " MSGS[x] ". sep " x " : "  SEPS[x]".");	##
        if(MSGSLEN==1) MSG0 = MSGSTR; # cimon en «split» : unua signo perdita ?
        else for (x=1 ; x<MSGSLEN ; x++)
        {
	  MSG0 = MSG0 MSGS[x] ;
	  ##print "x = " x;	##
	  if (SEPS[x] != "")
	  {
	    MSG0 = MSG0 " " MARK1 x MARK2 " ";
	    if( match(SEPS[ x ] ,"^<a *id *=") == 1 )
	    { # ne traduku «<a» HTML-etikedo
	      x0 = x ;
	      do
              {
                x++;
                SEPS[x0] = SEPS[x0] MSGS[x] SEPS[x];
              }
              while( x<=MSGSLEN && ! match(SEPS[x] ,"</a>"));
	    }
	    # ne traduku hiperligon, kodon, kursivigita kun "_"
	    else if( match(SEPS[ x ] ,"^ *`") == 1 )
	    { # kodo : ne traduku.
	      x0 = x ;
	      do
              {
                x++;
                SEPS[x0] = SEPS[x0] MSGS[x] SEPS[x];
              }
              while( x<=MSGSLEN && ! match(SEPS[x] ,"`"));
	    }
	    else if( match(SEPS[ x ] ,"^ *_$") == 1 )
	    { # kursivigita kun "_" : ne traduku
	      x0 = x ;
	      do
              {
                x++;
                SEPS[x0] = SEPS[x0] MSGS[x] SEPS[x];
              } while( (x <= MSGSLEN) && (match(SEPS[x] ,"^_[ \t]*")==0));
	    }
	    else if( match(SEPS[ x ] ,"[ \t]*!?\\[[ \t]*") == 1 )
	    { # hiperligo : traduku teksto,ne traduku ligo.
              ## print ("teksto hiperligo :" SEPS[ x ]);	##
	      x0 = x ;
	      do
              {
                x++;
	        MSG0 = MSG0 MSGS[x] ;
	        MSG0 = MSG0 " " MARK1 x MARK2 " ";
		# FARENDA prilabori la _ inter la [
	        if( match(SEPS[ x ] ,"^ *_$") == 1 )
	        { # kursivigita kun "_" : ne traduku
	          x1 = x ;
	          do
                  {
                    x++;
                    SEPS[x1] = SEPS[x1] MSGS[x] SEPS[x];
                  } while( (x <= MSGSLEN) && (match(SEPS[x] ,"^_[ \t]*")==0));
	        }
              }
              while( x<=MSGSLEN && ! match(SEPS[x] ," *\\] *"));
              ## print ("teksto hiperligo endo :" SEPS[ x ]);	##
	      x1 = x;
	      if( match(SEPS[ x ] ," *\\]\\( *") )
	      {
                ## print ("hiperligo  :" SEPS[ x ]);	##
	        do
                {
                  x++;
                  SEPS[x1] = SEPS[x1] MSGS[x] SEPS[x];
                }
                while( x<=MSGSLEN && ! match(SEPS[x] ," *\\) *"));
              }
              else
	      {
                x--;
              }
	    }
	  }
	}
        ##print("\nMSG0 " MSG0);	##
        BASEDIR"/traduko.sh " src " " dst " \"" MSG0 "\"" |getline MSG
        ##print("MSG " MSG);		##
        ##print("MSGSLEN=" MSGSLEN);    ##
	split(MSG, MSGS2, MARKEXPR ,SEPS2);
	MSGT="";
        DOSEPMAX=0;
        for (x=1 ; x<=length(MSGS2) ; x++)
	{ # anstataŭigi markoj per markdown-etikedojn
	  MSGT = MSGT MSGS2[x];
	  if (SEPS2[x] != "")
	  {
	    match(SEPS2[x],"[0-9]+");
	    x2 = substr(SEPS2[x],RSTART,RLENGTH);
	    ##print("x2=" x2);		##
	    if (x2 == (MSGSLEN-1) && match(SEPS[x2]," *\\\\n" ))
              DOSEPMAX=1
            else
              MSGT = MSGT SEPS[x2];
          }
	}
	if (match(SEPS[MSGSLEN-1]," *\\\\n" ))
          MSGT = MSGT SEPS[MSGSLEN-1];
        print(MSGT "\"");
      }
      print $0;
    }
    FUZZY=0;
    MATTER="";
  }
  else if (substr($0,1,28) == "#. type: YAML Front Matter: ")
  {
    MATTER=substr($0,29);
    print $0;
  }
  else if (substr($0,1,15) == "#. type: Fenced")
  {
    MATTER="Fenced";
    print $0;
  }
  else
  {
    print $0;
  }
}

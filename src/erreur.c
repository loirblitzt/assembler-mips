
/** Gestion des erreurs pour les directives et les instructions **/
#include "erreur.h"

int erreurDirective(STATEG2 state, char *lex2){
  long int lex = strtol(lex2,NULL,0);
  if (state==battArgByte){
    if (-128<=lex&& lex<=127){
      return(1);
    }
    return(0);
  }

  else if (state==battArgWord){
    if (-2147483648<=lex && lex<=2147483647){
    return(1);
  }
  return(0);}
  else if (state==battArgSpace){
    if (0<=lex /* && lex.space<=32 */){
      return(1);
    }
  return(0);
  }
  else if (state==attArgAsciiz){
    if (strlen((char*)lex2)<18){ /* a verif */
    return(1);
  }
  return(0);
  }
}

int erreurInstruction(LIST lex, TEXTCOL textc, INSTR * dico, int sizeDico){

  int indiceDico = textc.l->instr;
  long int val ;
  if (lex->type == registre){
      val = strtol((lex->data)+1,NULL,0);
    }
  if(dico[indiceDico].type=='R'){
    if(lex->type==registre)
    {
      if(val>32 || val<0){
        printf("La valeur d'un des registres n'est pas valide \n");
        return(0);
      }
      else{return(1);}
      if(lex->type=symb){
        /**jesaispas on verra**/
      }
      else{return(1);}

    }
    else{
      printf("L'opérande n'est pas du bon type\n");
      return(0);
      }
  }


  else if(dico[indiceDico].type=='I'){
    if(dico[indiceDico].numOp==3){
      if(((textc.l->op)[0]==NULL ) || ((textc.l->op)[1]==NULL)){
        if(lex->type==registre){

          if(val>31 || val<0){
            printf("La valeur d'un des registres n'est pas valide \n");
            return(0);}
          else{return(1);}

          }
      else if (lex->type==symb){/* if(){}
        else{return(1);} */
            }
      else{printf("Les opérandes portant sur les registres ne sont pas du bons types\n");
        return(0);}
      }

    else if(((textc.l->op)[0]!=NULL )|| ((textc.l->op)[1]!=NULL )&& (textc.l->op)[2]==NULL){
      if (lex->type==hexa || lex->type==decimal){

        long int d = strtol(lex->data,NULL,0);
        if(d<-32768 || d>32767){
          printf("La valeur de l'immediate n'est pas valide \n");
          return(0);
        }
        else{return(1);}

      }
      else if( lex->type == symb){
      /* manage etiqu */
      }
    else{printf("L'immediate n'est pas du bon type");
      return(0);
    }
    }
  }
  else if(dico[indiceDico].numOp==2){
    if(((textc.l->op)[0]==NULL ) || ((textc.l->op)[1]==NULL)){
      if(lex->type==registre){

        if(lex->data>31 || lex->data<0){
          printf("La valeur d'un des registres n'est pas valide \n");
          return(error);}
        else{return(1);}

        }
    else if (lex->type==symb){/* if(){}
      else{return(1);} */
          }
    else{printf("Les opérandes portant sur les registres ne sont pas du bons types\n");
      return(error);}
    }

  else if(((textc.l->op)[0]=!NULL ) && (textc.l->op)[1]==NULL){
    if (lex->type==hexa || lex->type==decimal){

      int d = strtol(lex->data,NULL,0);
      if(lex->data<-32768 || lex->data>32767){
        printf("La valeur de l'immediate n'est pas valide \n");
        return(error);
    }
    else{return(1);}

  }
  else{printf("L'immediate n'est pas du bon type");
  return(error);}
    }

  }
  else if(dico[indiceDico].numOp==0){printf("sans opérande, pas de soucis\n");
    return(1);}
}

  else if(dico[indiceDico].type=='S'){
    if(((textc.l->op)[0]==NULL) || ((textc.l->op)[1]==NULL)){
      if(lex->type==registre){

        if(val>31 || val<0){
          printf("La valeur d'un des registres n'est pas valide \n");
          return(0);}
          else{return(1);}

        }
    else if (lex->type==symb){/* if(){}
      else{return(1);}*/
      }
    else{printf("Les opérandes portant sur les registres ne sont pas du bons types\n");
      return(0);}
    }

  else if((textc.l->op)[0]!=NULL ||(textc.l->op)[1]!=NULL && (textc.l->op)[2]==NULL){
    if (lex->type==hexa || lex->type==decimal){

      int d = strtol(lex->data,NULL,0);
      if(d<0 || d>31){
        printf("La valeur du décalage n'est pas valide \n");
        return(0);
    }
    else{return(1);}

  }
  else{printf("Le décalage n'est pas du bon type");
  return(0);}

  }
}

else if(dico[indiceDico].type=='B'){
  if((textc.l->op)[0]==NULL){
    if(lex->type==registre){

      if(val>31 || val<0){
        printf("La valeur d'un des registres n'est pas valide \n");
        return(0);}
        else{return(1);}

      }
  else if (lex->type==symb){/* if(){}
    else{return(1);} */
    }
  else{printf("Les opérandes portant sur les registres ne sont pas du bons types\n");
    return(0);}
  }
  else if((textc.l->op)[0]!=NULL && (textc.l->op)[1]==NULL){
    /** gestion de l'oFFset?**/
  }
  else{printf("L'opérande n'est pas du bon type");
  return 0;}
}

  else if(dico[indiceDico].type=='L'){
    if(dico[indiceDico].numOp==3){
      if((textc.l->op)[0]==NULL ||(textc.l->op)[1]==NULL){
        if(lex->type==registre){

          if(val>31 || val<0){
            printf("La valeur d'un des registres n'est pas valide \n");
            return(0);}
            else{return(1);}

          }
      else if (lex->type==symb){/* if(){}
        else{return(1);} */
      }
      else{printf("Les opérandes portant sur les registres ne sont pas du bons types\n");
        return(0);}
      }

    else if((textc.l->op)[0]!=NULL ||(textc.l->op)[1]!=NULL && (textc.l->op)[2]==NULL){
      if (lex->type==hexa || lex->type==decimal){

        long int d = strtol(lex->data,NULL,0);
        if(d<-131071 || d>131070 || d%4!=0){/* a check */
          printf("La valeur du jump n'est pas valide \n");
          return(0);
      }
      else{return(1);}

    }
    else{printf("Le jump n'est pas du bon type");
    return(0);}

    }
  }
  else if(dico[indiceDico].numOp==2){
    if((textc.l->op)[0]==NULL){
      if(lex->type==registre){

        if(val>31 || val<0){
          printf("La valeur d'un des registres n'est pas valide \n");
          return(0);}
          else{return(1);}

        }
    else if (lex->type==symb){/* if(){}
      else{return(1);} */
    }
    else{printf("Les opérandes portant sur les registres ne sont pas du bons types\n");
      return(0);}
    }

  else if((textc.l->op)[0]!=NULL && (textc.l->op)[2]==NULL){
    if (lex->type==hexa || lex->type==decimal){

      long int d = strtol(lex->data,NULL,0);
      if(d<-131071 || d>131070 || d%4!=0){/* a check */
        printf("La valeur du branchement n'est pas valide \n");
        return(0);
    }
    else{return(1);}

  }
  else{printf("Le branchement n'est pas du bon type");
  return(0);}

  }

  }
  }

  else if(dico[indiceDico].type=='A'){
      if(((textc.l->op)[0]==NULL) ||(textc.l->op)[1]==NULL){
                if(lex->type==registre){

          if(val>31 || val<0){
            printf("La valeur d'un des registres n'est pas valide \n");
            return(0);}
            else{return(1);}

          }
      else if (lex->type==symb){/* if(){}
         else{return(1);} */
      }
      else{printf("Les opérandes portant sur les registres ne sont pas du bons types\n");
        return(0);}
      }

    else if(((textc.l->op)[0]!=NULL ||(textc.l->op)[1]!=NULL) && (textc.l->op)[2]==NULL){
      if (lex->type==hexa || lex->type==decimal){

        long int d = strtol(lex->data,NULL,0);
        if(d<-134217728 || d>134217727|| d%4!=0){/* a check */
          printf("La valeur du jump n'est pas valide \n");
          return(0);
        }
      }
      else{return(1);}

    }
    else{printf("Le jump n'est pas du bon type");
    return(0);}

    }
    else{printf("Le type d'instruction n'est pas bon");
    return(0);}
}

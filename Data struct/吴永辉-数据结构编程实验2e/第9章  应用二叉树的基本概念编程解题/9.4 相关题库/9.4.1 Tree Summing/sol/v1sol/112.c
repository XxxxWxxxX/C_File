#include <stdio.h>
#include <ctype.h>


/*************************************************
 problem 1 (solution a): 1992 Duke Internet Programming Contest
 written by: Owen Astrachan
*************************************************/


enum TreeKind {emptytree,yespath,nopath};
static enum TreeKind ParseTree(int);
static void SkipWhite();

int main()
{


    int target;

    while (!feof(stdin)){
	scanf("%d",&target);
	if (ParseTree(target) == yespath){
	    printf("yes\n");
	}
	else{
	    printf("no\n");
	}
	SkipWhite();
    }

    exit(0);
}

static void
SkipWhite()
{
    int c;

    do {
	c = getc(stdin);
    } while (isspace(c));

    ungetc(c,stdin);
}

static enum TreeKind
ParseTree(int target)
{
    int c,val;

    enum TreeKind left,right;
    
    SkipWhite();
    c = getc(stdin);
    
    /* all expressions start with left-paren */
    
    if (c != '('){
	fprintf(stderr,"error, expecting ( got %c\n",c);
    }
    SkipWhite();
    c = getc(stdin);

    /* after left-paren comes tree (possibly empty */
    
    if (isdigit(c) || c == '-' || c == '+'){
	ungetc(c,stdin);
	scanf("%d",&val);
	left = ParseTree(target - val);
	right = ParseTree(target - val);
	SkipWhite();
	c = getc(stdin);
	if (c != ')'){
	    fprintf(stderr,"error, expecting ) got %c\n",c);
	}

	/* check to see if "current" node is a leaf */
	
	if (left == emptytree && right == emptytree && target == val)
	    return yespath;

	/* not a leaf, check if path exists to left or to right */
	
	else if (left == yespath || right == yespath)
	    return yespath;
	
	return nopath;
    }

    /* s-expression ends with right-paren */
    
    if (c != ')'){
	fprintf(stderr,"error, expecting ) got %c\n",c);
    }

    return emptytree;
    
}

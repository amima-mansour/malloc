int main (){
int i;
char *addr;
char *s;
char *s1;
char *s2;
char *s3;
char *s4;

s = (char*)calloc(4, 1);
s[0] = 42;
s1 = calloc(4, 1);
s[0] = 42;
s2 = calloc(176, 1);
s2[0] = 42;
s3 = calloc(80, 1);
show_alloc_mem();
free(s);
free(s1);
s4 = calloc(32, 1);
show_alloc_mem();
free(s2);
free(s3);
show_alloc_mem();
return (0);
}

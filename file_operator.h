int write_to_file(const char *filename, char *buffer)
{
  FILE *fp;
//  char buffer[255];
  fp=fopen(filename,"w+");
  fprintf(fp,buffer);
//  fscanf(fp,"%s",buffer);
// printf("%s",buffer);
  fclose(fp);      
  return 0;
}

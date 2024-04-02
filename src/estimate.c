#include <stdio.h>
#include <stdlib.h>




void printarr(int r, int c, double **arr){
   for(int i=0;i<r;i++){
       for(int j=0;j<c;j++){
           printf("%lf", arr[i][j]);
           printf("%s", " ");
       }
       printf("\n");
   }
}


void transpose(int rows, int cols, double **mat, double **transposed){
   for(int i=0;i<rows;i++){
       for(int j=0;j<cols;j++){
           transposed[j][i] = mat[i][j];
       }
   }


}


void multiply(int r1, int c1, int c2, double **mat1, double **mat2, double **product){
 


   for ( int i = 0; i < r1; i++) {
       for ( int j = 0; j < c2; j++) {
           product[i][j] = 0;
           for (int k = 0; k < c1; k++) {
               product[i][j] += mat1[i][k] * mat2[k][j];
           }
       }
   }


 
}
void invert(int n, double **mat, double **inverted) {
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++) {
           inverted[i][j] = (i == j) ? 1.0 : 0.0;
       }
   }


   
   for (int p = 0; p < n; p++) {
       double f = mat[p][p];
       for (int j = 0; j < n; j++) {
           mat[p][j] /= f;
           inverted[p][j] /= f;
       }
       for (int i = 0; i < n; i++) {
           if (i != p) {
               f = mat[i][p];
               for (int j = 0; j < n; j++) {
                   mat[i][j] -= mat[p][j] * f;
                   inverted[i][j] -= inverted[p][j] * f;
               }
           }
       }
   }
}







int main(int argc, char const *argv[]){
  
   FILE *train_file, *data_file;
   train_file = fopen(argv[1], "r");
   data_file = fopen(argv[2], "r");
       if(!train_file || !data_file) exit(EXIT_FAILURE);


   
      


   char file_name1[10], file_name2[10];
   fscanf(train_file, "%s", file_name1);
   fscanf(data_file, "%s", file_name2);


   
   int Trows, Tcols;
   fscanf(train_file, "%d", &Tcols);
   fscanf(train_file, "%d", &Trows);




   double **train_x;
   train_x = (double **)malloc(Trows * sizeof(double *));
   for (int i = 0; i < Trows; i++) {
       train_x[i] = (double *)malloc((Tcols+1) * sizeof(double));
   }
   double **training_y;
   training_y = (double **)malloc(Trows * sizeof(double *));
   for (int i = 0; i < Trows; i++) {
       training_y[i] = (double *)malloc((1) * sizeof(double));
   }

   
   for(int i=0;i<Trows;i++){
       train_x[i][0] = 1.0;
   }


  
   for(int i=0;i<Trows;i++){
       for(int j=1;j<(Tcols+2);j++){
           double num;
           fscanf(train_file, "%lf", &num);


           
           if(j==(Tcols+1)){ 
               training_y[i][0] = num;
           }
           else{
               train_x[i][j] = num;
           }
       }
   }


   
   int Drows, Dcols;
   fscanf(data_file, "%d", &Dcols);
   fscanf(data_file, "%d", &Drows);


   double **data_x;
   data_x = (double **)malloc(Drows * sizeof(double *));
   for (int i = 0; i < Drows; i++) {
       data_x[i] = (double *)malloc((Dcols+1) * sizeof(double));
   }


   
   for(int i=0;i<Drows;i++){
       data_x[i][0] = 1.0;
   }


   
   for(int i=0;i<Drows;i++){
       for(int j=1;j<Dcols+1;j++){
           double num;
           fscanf(data_file, "%lf", &num);
           data_x[i][j] = num;


       }
   }
   
    fclose(train_file);
    fclose(data_file);





   double **transposed;
   transposed = (double **)malloc((Tcols+1 )* sizeof(double *));
   for (int i = 0; i < (Tcols+1); i++) {
       transposed[i] = (double *)malloc(Trows * sizeof(double));
   }
   
   transpose(Trows, (Tcols+1), train_x, transposed);



   double **product;
   product = (double **)malloc((Tcols+1)* sizeof(double *));
   for (int i = 0; i < (Tcols+1); i++) {
       product[i] = (double *)malloc((Tcols+1) * sizeof(double));
   }
  
   multiply(Tcols+1, Trows, (Tcols+1), transposed, train_x, product);



   double **inverted;
   inverted = (double **)malloc((Tcols+1) * sizeof(double *));
   for (int i = 0; i < (Tcols+1); i++) {
       inverted[i] = (double *)malloc((Tcols+1) * sizeof(double));
   }
   invert((Tcols+1), product, inverted);



   double **newproduct;
   newproduct = (double **)malloc((Tcols+1) * sizeof(double *));
   for (int i = 0; i < (Tcols+1); i++) {
       newproduct[i] = (double *)malloc(Trows * sizeof(double));
   }
   
   multiply((Tcols+1), (Tcols+1), Trows, inverted, transposed, newproduct);


   double **W;
   W = (double **)malloc((Tcols+1) * sizeof(double *));
   for (int i = 0; i < (Tcols+1); i++) {
       W[i] = (double *)malloc(1 * sizeof(double));
   }
   
   multiply((Tcols+1), Trows, 1, newproduct, training_y, W);



   double **Y;
   Y = (double **)malloc(Drows * sizeof(double *));
    for (int i = 0; i < Drows; i++) {
          Y[i] = (double *)malloc(1 * sizeof(double));
    }
   
   multiply(Drows, Dcols+1, 1, data_x, W, Y);


   for (int i = 0; i < Drows; i++) {
      printf("%.0f\n", Y[i][0]);
   }



   for (int i = 0; i < Trows; i++) {
       free(train_x[i]);
       free(training_y[i]);
   }
   free(train_x);
   free(training_y);


   for (int i = 0; i < Drows; i++) {
       free(data_x[i]);
   }
   free(data_x);


   for (int i = 0; i < Tcols+1; i++) {
       free(transposed[i]);
       free(product[i]);
       free(inverted[i]);
       free(newproduct[i]);
       free(W[i]);
   }
   free(transposed);
   free(product);
   free(inverted);
   free(newproduct);
   free(W);


   for (int i = 0; i < Drows; i++) {
       free(Y[i]);
   }
   free(Y);


  
   return EXIT_SUCCESS;


}

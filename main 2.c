//Kaosar CSE 06807943
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <process.h>
# define true 0
# define false 1

struct product{
    char product_name[30];
    char product_id[6];
    double quantity;
    double discount;
    int num_sale;
    double unit_price;
    double total_price;
};

struct product product_var[100]; // maximum number of product
int count = 0; //update for each entry

FILE *fp, *hp; // File Pointer

void write_file();  // function to save inputs into a file
int read_files();  //Function to read outputs from file
int add_product(); //add products to the file
int show_product(); //display the products in inventory
void edit_entry(); //Edit any individual entry
void delete_product(); // delete entire entry of an entered valid id
void make_order();
int id_checker(int i, int j); // checks the id

int main()
{
    int choice;

    printf("\t\t\t============================================\n");
    printf("\t\t\t\tInventory Management System\n");
    printf("\t\t\t============================================\n");

   do{
    printf("Menu :\n");
    printf("1) Press 1 to Entry Products.\n");
    printf("2) Press 2 to Show the Inventory.\n");
    printf("3) Press 3 to Edit any Entry.\n");
    printf("4) Press 4 to Delete any Entry.\n");
    printf("5) Press 5 to Make an  Order.\n");
    printf("6) Press 6 to Exit the Program.\n");
    printf("Choice ========> ");

    scanf("%d", &choice);

    ch:
    switch(choice)
    {
        case 1 : add_product(); break;
        case 2 : show_product(); break;
        case 3 : edit_entry(); break;
        case 4 : delete_product(); break;
        case 5 : make_order(); break;
        case 6 : exit(1); break;
        default : printf("wrong choice.\n"); goto ch; break;
    }


    }while(1);

    getch();
    return 0;
}

void write_file()
{
    int i;
    fp = fopen("Inventory.txt", "w");
    if (fp == NULL)
     {
         perror("Invalided File!!!!"); // printing a error
         return EXIT_FAILURE;
     }

     fprintf(fp, "%d\n", count);

     for(i = 0; i < count; i++){
        fputs(product_var[i].product_id,  fp);
        fprintf(fp, "\n");

        fputs(product_var[i].product_name,  fp);
        fprintf(fp, "\n");

        fprintf(fp, "%lf\n", product_var[i].quantity);
        fprintf(fp, "%lf\n", product_var[i].unit_price);
        fprintf(fp, "%lf\n", product_var[i].discount);
        fprintf(fp, "%d\n", product_var[i].num_sale);
        fprintf(fp, "%lf\n", product_var[i].total_price);
     }

     fclose(fp);
}

int read_file()
{
    int n = 0, i;

    fp = fopen("Inventory.txt", "r");
    if(fp == NULL)
    {
        return EXIT_FAILURE;
    }
    fscanf(fp, "%d\n", &n);

    for(i = 0; i < n; i++)
    {
        fgets(product_var[i].product_id, 6 , fp);
        product_var[i].product_id[strlen(product_var[i].product_id) - 1 ] = 0;// new line remover

        fgets(product_var[i].product_name, 30, fp);
        product_var[i].product_name[strlen(product_var[i].product_name) - 1] = 0; //removes new line

        fscanf(fp, "%lf", &product_var[i].quantity);
        fscanf(fp, "%lf", &product_var[i].unit_price);
        fscanf(fp, "%lf", &product_var[i].discount);
        fscanf(fp, "%d",  &product_var[i].num_sale);
        fscanf(fp, "%lf\n", &product_var[i].total_price);
    }
    fclose(fp);

    return n;
}

int add_product()
{
    printf("\n\nEnter New Products ======>\n");
    read_file();

    if(count > 0)
    {
        count = read_file();
        id_checker(0, count);
    }
    else{
    printf("\nProduct ID : ");
    fflush(stdin);
    gets(product_var[count].product_id);
    }

    printf("Product Name : ");
    gets(product_var[count].product_name);

    printf("Enter Quantity : ");
    scanf("%lf", &product_var[count].quantity);

    printf("Enter Unit Price : ");
    scanf("%lf", &product_var[count].unit_price);

    printf("Enter Discount : ");
    scanf("%lf", &product_var[count].discount);

    printf("Enter Number of Sale : ");
    scanf("%d", &product_var[count].num_sale);

    product_var[count].total_price = product_var[count].quantity * product_var[count].unit_price;

    count++;

    write_file();

  return 0;

}

int show_product()
{
   int i;
   count = read_file();
   hp = fopen("display.html", "w");
    if(hp == NULL)
    {
        perror("File can not be found!!\n");
        return EXIT_FAILURE;
    }
   if(count < 0)
    printf("Cannot open file\n");

   fprintf(hp, "<html> <title>Display</title> <body bgcolor=\"#FFD998\">");
   fprintf(hp, "<table align=\"center\" border=\"2\" width=\"700\">");
   fprintf(hp, "<h2 align=\"center\">\t\t\t\t************* Inventory *************</h2>\n");
   fprintf(hp, "<tr> <th>S.l</th> <th>Product ID</th> <th>Product Name</th> <th>Quantity</th> <th>Unit Price</th> <th>Discount</th> <th>Total Sold</th> <th>Total Price</th></tr>\n");
   for(i = 0; i < count; i++)
   {
    fprintf(hp,"<tr> <td>%d</td> <td>%s</td> <td>%s</td> <td>%.2lf</td> <td>%0.2lf</td> <td>%.2lf %%</td> <td>%d</td> <td>%.2lf</td> </tr>\n", i+1, product_var[i].product_id, product_var[i].product_name, product_var[i].quantity, product_var[i].unit_price, product_var[i].discount, product_var[i].num_sale, product_var[i].total_price);

   }
   fprintf(hp, "</table> </body> </html>\n");
   fclose(hp);

  system ("Start display.html");

   return 0;
}

void edit_entry()
{
    char id[6];
    int t, i ,ch;

    printf("\n\nEdit a Product ======>\n\n");
    fflush(stdin);

    printf("Enter the ID of product that you want to change :\n");
    gets(id);

    read_file();
    {


    for(i = 0; i < count; i++)
    {
        if(strcmp(id,product_var[i].product_id) != 0) // whether input id match or
        {
            write_file();
        }

        else{
            printf("\n* Enter 1 to Update product ID.");
            printf("\n* Enter 2 to Update product Name.");
            printf("\n* Enter 3 to Update product Quantity.");
            printf("\n* Enter 4 to Update product Unit Price.");
            printf("\n* Enter 5 to Update product Discount.");
            printf("\n* Enter 6 to Update product Total Sale.");
            printf("Enter your choice : ");
            scanf("%d", &ch);

            switch(ch)
            {
                case 1 : printf("Enter new ID : ");

                fflush(stdin);

                gets(product_var[i].product_id);
                break;

                case 2 : printf("Enter new Product Name : ");

                fflush(stdin);

                gets(product_var[i].product_name);
                break;

                case 3 : printf("Enter new Quantity : ");

                scanf("%lf", &product_var[i].quantity);
                break;

                case 4 : printf("Enter new Unit Price : ");

                scanf("%lf", &product_var[i].unit_price);
                break;

                case 5 : printf("Enter new Discount : ");

                scanf("%lf", &product_var[i].discount);
                break;

                case 6 : printf("Enter new Total Sale : ");

                scanf("%d", &product_var[i].num_sale);
                break;

                default : printf("INVALID CHOICE : Try Again......\n");

            }

            write_file(); //save the entry
        }
    }
    }
    fclose(fp);

    fp = fopen("Inventory.txt", "r");

    read_file();
    {
        write_file(); //rechecking and rewriting the whole file
    }

    fclose(fp);

    printf("Product info updated......\n");

}

void delete_product()
{
    count = read_file();

    char id[6];

    int i,j;

    int z = false;

    printf("Enter the id that you want to delete : ");
    fflush(stdin);
    gets(id);

    for(i = 0; i < count; i++)
    {

        if(strcmp(id, product_var[i].product_id) == 0) // checking if the user input id matched any id
        {
            z = true;
            for(j = i; j < (count - 1); j++) // by this loop entered valid id will be deleted
            {
                product_var[j] = product_var[j+1];
            }
            count--;

            printf("Delete ID : %s successfully......\n", id);
        }
    }
    write_file();

    if(z == false)// no product id matched the entered id then it will execute
    {
      printf("Can't find entered product id : %s\n", id);
    }


}

void make_order()
{
    double qnty;
    int i;
    char id[6];
    double temp_sale;

    int z = false;
    count = read_file();

    printf("\n\nMake an Order =======>\n\n");
    printf("Product ID : ");
    fflush(stdin);

    gets(id);

    for(i = 0; i < count; i++)
    {
        if(strcmp(id, product_var[i].product_id) == 0)
        {
            z = true;

            printf("\n\nProduct ID found\n\n");
            printf("Product ID : %s\n", product_var[i].product_id);
            printf("Product Name : %s\n", product_var[i].product_name);
            printf("Product Price : %0.2lf\n", product_var[i].unit_price);

            printf("Please Enter the quantity you want to buy : ");
            scanf("%lf", &qnty);

            if(qnty > product_var[i].quantity)
            {
                printf("Insufficient Quantity!!!!!!");
                break;
            }

            product_var[i].quantity = product_var[i].quantity - qnty;
            product_var[i].num_sale += (int) qnty;

            temp_sale = qnty * product_var[i].unit_price;

            product_var[i].total_price -= temp_sale;

            printf("\n\n\t\t====Your Order====\n\n");

            printf("ID : %s\n", product_var[i].product_id);
            printf("Name : %s\n", product_var[i].product_name);
            printf("Quantity : %lf\n", qnty);
            printf("Unit Price : %lf\n", product_var[i].unit_price);
            printf("Total Price : %lf\n", temp_sale);

        }
    }

    if (z == false)
    {
        printf("Can't find the product id ......\n");
    }
    write_file();
}

int id_checker(int i, int j)
{
    count = read_file();

    printf("Product ID : ");
    fflush(stdin);

    gets(product_var[count].product_id);

    if(strcmp(product_var[i].product_id, product_var[j].product_id) == 0)
    {
        printf("Id number  already exists. Give another Id.\n");

        return id_checker(i++, j--);
    }


}

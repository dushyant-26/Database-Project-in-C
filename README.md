# Basic Operations of Database
  
**\-** `Database` is an organized collection of structured information, or data, typically stored electronically in a computer system.  
**\-** `Database` provides various operations to ease the storage and retrieval of data  
**\-** `Database` manages the data and helps to reduce data redundancy  

**This project is designed keeping in mind basic operations of a database.**  
This project is made using file system in c.

``` bash
Note:  
This project is not platform independent at this moment.  
So it can only be run on Linux system.
```

## Steps to execute the project into your system

* Clone this repository into your system
* Run the ***make*** command
* Now execute **./Database** whenever you want to access the database.

## Operations of `Database` Included in Project

* ***C*** - Create Operation
* ***R*** - Read Operation
* ***U*** - Update Operation
* ***D*** - Delete Operation

### `Create Operation`

This includes -

* Creation of table i.e setting attributes and their datatype
* Inserting data into data table  

#### Methods of Create Operation ->

* ***Table\* getTable()***  

>This method takes input from user and creates a database table accordingly and return **Table\***. If table already exist,it will just return pointer to it.

* ***void insert(Table\* table)***  

>This method take **Table\*** as parameter. It takes input from user and add that entry to the database accordingly

### `Read Operation`

This includes -

* Reading any particular entry from database.
* Reading the complete database.
* Reading the structure of table created.
* Reading the data using wildcard operator.

#### Methods of Read Operation ->

* ***void readData(Table\* table)***  

>This method will take **Table\*** as parameter. It takes input from user regarding constraint and display data according to the constraint added by user.  
All the data can be read by adding \* as a constraint.  
Wildcard operator(*) can be used to get the entries that contains matches to a wildCard search string.

* ***void readTableStructure(Table\* table)***  

>This method will take **Table\*** as parameter.  
This displays the various attributes of table including its name, attributes and their datatypes.

### `Update Operation`

This includes -

* Updating data of any entry in database
* Updating data of all the entries.

#### Methods of Update Operation ->

* ***void updateData(Table\* table)***  

>This method will take **Table\*** as parameter. It takes input from user regarding new data and constraint and update the data in database according to the constraint added by user.  
All the data can be updated by adding \* as a constraint.

### `Delete Operation`

This includes -

* Deleting any particular entry from database
* Deleting all the data from database
* Deleting the database itself i.e data as well as structure of database

#### Methods of Delete Operation ->

* ***void deleteData(Table\* table)***  

>This method will take **Table\*** as parameter. It takes input from user regarding constraint and delete data according to the constraint added by user.
All the data can be deleted by adding \* as a constraint.

* ***void truncate(Table\* table)***  

>This method will take  **Table\*** as parameter and make the database empty.

* ***void deleteTable(Table\* table)***  

>This method will take **Table\*** as parameter and delete the table data along with the table structure.
  
## Creating your own UI for database using these functions

 To make use of these functions, you need to include the following files.

* **createOperations.h**  
* **readOperations.h**  
* **updateOperations.h**  
* **deleteOperations.h**

> Firstly, You need to run getTable() function, and store the returned Table\*.  
Now you can use other function for database by passing this Table\* as argument.

## Future Goals

More features to be added in future -

* ***Indexing***
* ***Query language implementation***
* ***Transaction***
* ***Commit and Rollback option***
* ***Providing Data Security***


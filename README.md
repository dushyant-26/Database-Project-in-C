# Basic Operations of Database

**This project is designed keeping in mind basic operations of a database.**  
**\-** ***Database*** is an organized collection of structured information, or data, typically stored electronically in a computer system.  
**\-** ***Database*** provides various operations to ease the storage and retrieval of data  
**\-** ***Database*** manages the data and helps to reduce data redundancy

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

>This method creates a database table according to user input and return **Table\***. If table already exist,it will just return pointer to it.

* ***void insert(Table\* table)***  

>This method take **Table\*** as parameter and input entry from user and add that entry to the database

### `Read Operation`

This includes -

* Reading any particular entry from database.
* Reading the complete database.

#### Methods of Read Operation ->

* ***void readData(Table\* table)***  

>This method will take **Table\*** as parameter and input from user regarding constraint and display data according to the constraint added by user.

### `Update Operation`

This includes -

* Updating data of any entry in database

#### Methods of Update Operation ->

* ***void updateData(Table\* table)***  

>This method will take **Table\*** as parameter and input from user regarding new data and constraint and update the data in database according to the constraint added by user.

### `Delete Operation`

This includes -

* Deleting any particular entry from database
* Deleting all the data from database
* Deleting the database itself i.e data as well as structure of database

#### Methods of Delete Operation ->

* ***void deleteData(Table\* table)***  

>This method will take **Table\*** as parameter and input from user regarding constraint and display data according to the constraint added by user.

* ***void truncate(Table\* table)***  

>This method will take  **Table\*** as parameter and make the database empty.

* ***void deleteTable(Table\* table)***  

>This method will take **Table\*** as parameter and delete the table data along with the table structure.

## Future Goals

More features to be added in future -

* ***Indexing***
* ***Query language implementation***
* ***Transaction***
* ***Commit and Rollback option***
* ***Providing Data Security***


# Bootcamp Assignment 2: Persisting data using MongoDB and Mongoose

Our application at this point has an issue one major issue... 
- Each time the server starts, we reload the data from the same JSON file. 
 
It would be better if the data was stored elsewhere in a *persistent* fashion so that even if the server were to crash, our data would remain unharmed.

In this assignment, we will focus on persisting data by moving the JSON file to a dedicated database.  In our case, we will be using [MongoDB](https://www.mongodb.org/), which stores data as **documents**. These documents are very similar to JSON objects, making MongoDB a good candidate for our web application. 

### Mongoose
If you take a look at MongoDB's [introductory documentation](https://docs.mongodb.org/getting-started/node/introduction/), you will notice there's quite a bit of code that has to be written to add, find, update, or delete data using their APIs. [Mongoose](https://mongoosejs.com/docs/index.html) simplifies the process of communicating with MongoDB and also provides tools to organize/model the data into [**schemas**](https://mongoosejs.com/docs/guide.html). Schemas are used to pre-define the data's attributes, and the type each attribute will have. [Read this tutorial that discusses how to use Mongoose with Node.js - uses callbacks](https://scotch.io/tutorials/using-mongoosejs-in-node-js-and-mongodb-applications) or [uses promises](https://developerhandbook.com/mongodb/connect-mongo-atlas-mongoose/) before continuing with the assignment.

### MongoDB
Setting up MongoDB is fairly simple. Just run the mongo daemon (mongod) and then run the mongo shell in another terminal.
<br/>
- ##### MacOS
    > https://treehouse.github.io/installation-guides/mac/mongo-mac.html
- ##### Windows
    > https://treehouse.github.io/installation-guides/windows/mongo-windows.html
- #### Ubuntu
    > https://itsfoss.com/install-mongodb-ubuntu/
    
Once you are in the mongo shell you will see something like [this](https://i.imgur.com/tCZ6V6P.png). Once you are here, look up some of the mongo shell commands.
Some commands you'll be using frequently are:

- show dbs ==> shows you a list of all of the available databases
- show collections ==> shows you a list of all of the collections (SQL tables equivalent)
- use <db name> ==> allows you to switch to the specified database (a.k.a. using the database)
- db.collection.functionGoesHere({yourFilter: infoHere}) -> db.listings.find({code: "AAF"}) ==> finds ALL documents with a 'code' attribute with value 'AAF'
- db.dropDatabase() ==> drops the database that is currently in use
    

## Assignment Steps
___*setup*___:
1. Make sure to have MongoDB installed. 
2. Clone your repository, navigate into it, then install all necessary packages with `npm i`.
  
__*config.js*__:
1. Create a new file called `config.js` and copy the contents of `config.example.js` into it. 
2. Insert your MongoDB URI, which will be: `mongodb://127.0.0.1:27017/yourDatabaseName`

__*ListingSchema.js*__:
1. Define your schema. Make sure all required fields are _actually_ required.
2. The schema should consist of the following attributes:
    - code :: String && required
    - name :: String && required
    - coordinates: {latitude :: mongoose.Number, longitude :: mongoose.Number}
    - address :: String
3. Ensure your schema passes the tests by running `npm test` or `jest`. You will only pass the schema tests, it is okay to fail the rest of the tests for now.
4. If you are not sure what a schema is, please make sure to look into it!

An example schema might look like the following:

```js
const myPianoSchema = new mongoose.Schema({
   type: {type: String, required: true},                // a require string
   keycount: {type: mongoose.Number, required: true},   // a required number
   isElectronic: {type: Boolean},                       // a boolean that could either be true or false
   users: [String],                                     // an array of strings
   favoriteNotes: {                                     // you can have objects like this one, accessing the children as favoriteNotes.note1 or favoriteNotes.note2
       note1: {type: String},
       note2: {type: String}
   }
});
```

__*JSONtoMongo.js*__:
1. Read the `listings.json` JSON file and parse it, store the result in a variable.
2. Use the JSON that you parsed and use the model you create in `ListingSchema.js` to save the 'document' into the database (read up on how to save models to the database).
3. Make sure that either your code automatically clears the database on each test or you manually clear the database on each trial.

__*queries.js*__:
1. Follow the instructions given in the comments of the boiler plate code given. Follow the link given (and please Google on your own as well) to get a better understanding of querying with Mongoose.
2. Verify that your outputs are correct for each function defined.
3. Run `node queries.js`, it should print out all the listings!

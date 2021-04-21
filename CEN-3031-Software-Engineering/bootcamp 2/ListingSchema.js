/* Import mongoose and define any variables needed to create the schema */
import mongoose from 'mongoose';

/* Create your schema for the data in the listings.json file that will define how data is saved in your database
     See https://mongoosejs.com/docs/guide.html for examples for creating schemas
     See also https://scotch.io/tutorials/using-mongoosejs-in-node-js-and-mongodb-applications
  */


const listingSchema = new mongoose.Schema({
  /* Your code for a schema here */
  //Check out - https://mongoosejs.com/docs/guide.html
    code:
    {
        type: String, required: true, unique: true
    },
    name:
    {
        type: String, required: true, unique: false
    },
    coordinates:
    {
        latitude:
        {
            type: Number, required: false, unique: false
        },
        longitude:
        {
            type: Number, required: false, unique: false
        }
    },
    address:
    {
        type: String, required: false, unique: false
    }
});

listingSchema.pre('save', function (next)
{
    let date = new Date();

    this.updated_at = date;

    if (!this.created_at)
        this.created_at = date;

    next();
});

/* Use your schema to instantiate a Mongoose model
Export the model to make it avaiable to other parts of your Node application */
//Check out - https://mongoosejs.com/docs/guide.html#models
let Listing = mongoose.model('Listing', listingSchema);
export default mongoose.model('listings', listingSchema);


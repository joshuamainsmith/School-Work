/* Add all the required libraries*/

/* Connect to your database using mongoose - remember to keep your key secret*/

/* Fill out these functions using Mongoose queries*/
//Check out - https://mongoosejs.com/docs/queries.html

import mongoose from 'mongoose';
import Listing from './ListingSchema.js';
import config from './config.js';

mongoose.connect(config.db.uri, { useNewUrlParser: true }).then(success =>
{
    console.log("Connected to DB");
});

const findLibraryWest = () =>
{
  /* 
    Find the document that contains data corresponding to Library West,
    then log it to the console. 
   */
    Listing.findOne({ "name": "Library West" }, function (err, listing)
    {
        if (err)
        {
            console.log(err);
        }
        else
        {
            console.log("Library West Log: " + JSON.stringify(listing, null, 4));
        }
    });
};
const removeCable = () =>
{
  /*
    Find the document with the code 'CABL'. This cooresponds with courses that can only be viewed 
    on cable TV. Since we live in the 21st century and most courses are now web based, go ahead
    and remove this listing from your database and log the document to the console. 
   */
    Listing.findOne({ code: "CABL" }, function (err)
    {
        if (err)
        {
            console.log(err);
        }
    }).remove(function (err, listing)
    {
        if (!err)
        {
            console.log("CABL Deleted Listing " + JSON.stringify(listing, null, 4));
        }
    });
};
const updatePhelpsLab = () =>
{
  /*
    Phelps Lab address is incorrect. Find the listing, update it, and then 
    log the updated document to the console. 
    
    Correct Address: 1953 Museum Rd, Gainesville, FL 32603

   */
    Listing.findOne({ name: "Phelps Laboratory" }, function (err)
    {
        if (err)
        {
            console.log(err);

        }

    }).update({ address: "1953 Museum Rd, Gainesville, FL 32603" }, function (err)
    {
        if (err)
        {
            console.log(err);

        }
    }).then(function ()
    {
        Listing.findOne({ name: "Phelps Laboratory" }, function (listing)
        {

            console.log("Phelps Lab Updated Listing: " + listing);

        })
    });
};
const retrieveAllListings = () => {
  /* 
    Retrieve all listings in the database, and log them to the console. 
   */
    Listing.find(function (err, listings) {
        if (err)
        {
            console.log(err);
        }
        else
        {
            console.log("All DB Listings: " + JSON.stringify(listings, null, 4));
        }
    });
};

findLibraryWest();
removeCable();
updatePhelpsLab();
retrieveAllListings();

// 'use strict';
// /*
//   Import modules/files you may need to correctly run the script.
//   Make sure to save your DB's uri in the config file, then import it with a require statement!
//  */
// import * as fs from 'fs';
// import mongoose from 'mongoose';
// import Career from './models/CareerModel.js';
// import config from './config/config.js';
// import async from 'async';

const fs = require('fs'),
      mongoose = require('mongoose'),
      Career = require('../models/CareerModel.js'),
      CareerCluster = require('../models/CareerClusterModel.js'),
      config = require('../config/config.js'),
      async = require('async')

/* Connect to your database */
function clearAndRefill() {
    mongoose.connect(config.db.uri, {useNewUrlParser: true, useUnifiedTopology: true});
    /*
      Clears the connected database collection of listings
     */
    Career.deleteMany({}, (err) => {
        if (err) throw err;
    });
    CareerCluster.deleteMany({}, (err) => {
        if (err) throw err;
    });
    

    fs.readFile('./server/scripts/careers.json', 'utf8', (err, data) => {
        if (err) throw err;
        let careerData = JSON.parse(data);

        let clusters = {};

        async.forEach(careerData.entries, (doc, callback) => {
            Career.create(doc, (err) => {
                if (err) throw err;
                //callback();
            });
    
            if(!clusters[doc.type]) {
                clusters[doc.type] = 1;
            CareerCluster.create({name: doc.type}, (err) => {
                if (err) throw err;
                callback();
            })}
        }, () => {
            mongoose.connection.close();
        });
    });
};

clearAndRefill();

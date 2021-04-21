/* Import mongoose and define any variables needed to create the schema */
const mongoose = require('mongoose');


const careerClusterSchema = new mongoose.Schema({
  name: {type: String, required: true},
  description: String
}, {timestamps: true});

/* Use your schema to instantiate a Mongoose model
Export the model to make it avaiable to other parts of your Node application */
//Check out - https://mongoosejs.com/docs/guide.html#models
module.exports = mongoose.model('CareerCluster', careerClusterSchema);

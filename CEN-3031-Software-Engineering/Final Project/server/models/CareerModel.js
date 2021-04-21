/* Import mongoose and define any variables needed to create the schema */
const mongoose = require('mongoose');


const careerSchema = new mongoose.Schema({
  name: {type: String, required: true},
  type: {type: String, required: true},
  description: String,
  keywords: Array,
  salary_ranges: {
      entry: Number,
      median: Number,
      mean: Number
  },
  outlook: String,
  education: String,
  important_subjects: Array,
  video_link: String
});

careerSchema.index({'$**': 'text'})

/* Use your schema to instantiate a Mongoose model
Export the model to make it avaiable to other parts of your Node application */
//Check out - https://mongoosejs.com/docs/guide.html#models
module.exports = mongoose.model('Career', careerSchema);

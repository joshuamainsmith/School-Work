/* Import mongoose and define any variables needed to create the schema */
const mongoose = require('mongoose');
const bcrypt = require('bcrypt');


const userSchema = new mongoose.Schema({
  role: {type: String, enum: ['user', 'admin'], required: true, default: 'user'},
  password: {type: String, required: true},
  username: {type: String, required: true},
  email: String
}, {timestamps: true});


userSchema.pre('save', function(next) {
  if(!this.isModified('password'))
    return next();
  bcrypt.hash(this.password, 10, (err,passwordHash) => {
    if(err)
      return next(err);
    this.password = passwordHash;
    next();
  })
})

userSchema.methods.comparePassword = function(password,cb) {
  bcrypt.compare(password, this.password, (err, isMatch) => {
    if(err)
      return cb(err);
    else {
      if(!isMatch)
        return cb(null, isMatch);
      return cb(null, this);
    }
  })
}

/* Use your schema to instantiate a Mongoose model
Export the model to make it avaiable to other parts of your Node application */
//Check out - https://mongoosejs.com/docs/guide.html#models
module.exports = mongoose.model('User', userSchema);

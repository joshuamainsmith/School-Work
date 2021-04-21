const usersController = require('../controllers/UsersController.js'),
    User = require('../models/UserModel'),
    express = require('express'),
    usersRouter = express.Router()
    passport = require('passport'),
    passportConfig = require('../config/passport'),
    JWT = require('jsonwebtoken');
/*
  These method calls are responsible for routing requests to the correct request handler.
  Take note that it is possible for different controller functions to handle requests to the same route.

  Note: the listings variable above and the file it is connected to help you trace
*/
usersRouter.get('/', usersController.search);
usersRouter.post('/', usersController.create);

/*
  The ':' specifies a URL parameter.
*/
usersRouter.get('/logout/', passport.authenticate('jwt', {session: false}), (req, res) => {
  res.clearCookie('access_token');
  res.json({user: {username: "", role: ""}, success: true});
})

// usersRouter.get('/:userId', usersController.read);
usersRouter.put('/:userId', usersController.update);
usersRouter.delete('/:userId', usersController.remove);

const signToken = userID => {
  return JWT.sign({
    iss: process.env.COOKIE_SECRET || require('../config/config').cookie.secret,
    sub: userID
  }, process.env.COOKIE_SECRET || require('../config/config').cookie.secret, {expiresIn: "6h"});
}


usersRouter.post('/register', (req, res) => {
  const { username, password, role } = req.body;

  User.findOne({username}, (err, user) => {
    if(err) {
      res.status(500).json({message: {msgBody: "Error has occurred", msgError: true}});
    }

    if(user)
      res.status(400).json({message: {msgBody: "Username is already taken", msgError: true}});
    else {
      const newUser = new User({username, password, role});
      newUser.save(err => {
        if(err) {
          console.log(err)
          res.status(500).json({message: {msgBody: "Error has occurred", msgError: true}});
        } else {
          res.status(201).json({message: {msgBody: "Account successfully created", msgError: false}});
        }
      })
    }
  })
})

usersRouter.post('/login/', passport.authenticate('local', {session: false}), (req, res) => {
  if(req.isAuthenticated()) {
    const {_id, username, role} = req.user;
    const token = signToken(_id);
    res.cookie('access_token', token, {httpOnly: true, sameSite: true});
    res.status(200).json({isAuthenticated: true, user: {username,role}})
  }
});

usersRouter.get('/authenticated', passport.authenticate('jwt', {session: false}), (req, res) => {
  const {username, role} = req.user;
  res.status(200).json({isAuthenticated: true, user: {username, role}})
})

// Adding middleware to set param :listingId
usersRouter.param('userId', usersController.userByID);

module.exports = usersRouter;

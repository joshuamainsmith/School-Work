const careers = require('../controllers/CareersController.js'),
    express = require('express'),
    careersRouter = express.Router();
/*
  These method calls are responsible for routing requests to the correct request handler.
  Take note that it is possible for different controller functions to handle requests to the same route.

  Note: the listings variable above and the file it is connected to help you trace
*/
careersRouter.get('/', careers.search);
careersRouter.post('/', careers.create);

/*
  The ':' specifies a URL parameter.
*/
careersRouter.get('/:careerId', careers.read);
careersRouter.put('/:careerId', careers.update);
careersRouter.delete('/:careerId', careers.remove);

// Adding middleware to set param :listingId
careersRouter.param('careerId', careers.careerByID);

module.exports = careersRouter;

const careerClusters = require('../controllers/CareerClustersController.js'),
    express = require('express'),
    clustersRouter = express.Router();
/*
  These method calls are responsible for routing requests to the correct request handler.
  Take note that it is possible for different controller functions to handle requests to the same route.

  Note: the listings variable above and the file it is connected to help you trace
*/
clustersRouter.get('/', careerClusters.search);
clustersRouter.post('/', careerClusters.create);

/*
  The ':' specifies a URL parameter.
*/
clustersRouter.get('/:clusterId', careerClusters.read);
clustersRouter.put('/:clusterId', careerClusters.update);
clustersRouter.delete('/:clusterId', careerClusters.remove);

// Adding middleware to set param :listingId
clustersRouter.param('clusterId', careerClusters.clusterByID);

module.exports = clustersRouter;

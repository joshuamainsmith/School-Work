/* Dependencies */
// import mongoose from 'mongoose';
// import Career from '../models/CareerClusterModel.js';

const mongoose = require('mongoose'),
	Cluster = require('../models/CareerClusterModel.js');

// const Example = require('../models/examples.server.model.js')
//
// exports.hello = function(req, res) {
//     res.send('world')
// };

exports.create = async (req, res) => {

    let cluster = req.body;

    Cluster.create(cluster, function (err, cluster) {
        if (err) {
            res.status(400).send(err);
        } else {
            res.send(cluster);
        }
    });
};

exports.read = (req, res) => {
	/* send back the cluster as json from the request */
	/* If the cluster could _not_ be found, be sure to send back a response in the following format: {error: 'Some message that indicates an error'} */
	// Error response is handled by clusterByID
	res.send(req.cluster);
};

/* Update a cluster - note the order in which this function is called by the router*/
exports.update = (req, res) => {
	const cluster = req.cluster;
	if (cluster) {
		Cluster.findOneAndUpdate({ _id: cluster._id }, req.body, { new: true }, function(err, cluster) {
			if (err) {
				res.status(400).send(err);
			} else {
				res.send(cluster);
			}
		});
	}
};

exports.remove = (req, res) => {
	let clusterId = req.params.clusterId;

	Cluster.findOneAndDelete({ _id: clusterId }, function(err, cluster) {
		if (err) return handleError(err);

		if (cluster) {
			res.sendStatus(200);
		} else {
			// Sending a 404 with an error message if cluster is not found
			// debating if this should be a 404 or a 200 as the tests expect a
			// 200 whe the cluster is not found, but I believe 404 makes more sense
			res.status(404).json({ error: 'Career was not found.' });
		}
	});
};

exports.search = (req, res) => {
    let keyword = req.query.keyword

    if (keyword) {
      Cluster.find({$text: {$search: keyword}}).sort({code: 1}).exec(function(err, clusters) {
          if (err) {
              res.status(400).json({error: 'There was an issue with your request.'})
          } else {
              res.send(clusters);
          }
      });
    } else {
      Cluster.find({}).sort({code: 1}).exec(function(err, clusters) {
          if (err) {
              res.status(400).json({error: 'There was an issue with your request.'})
          } else {
              res.send(clusters);
          }
      });
	}
};

/*
    Middleware: find a cluster by its ID, then pass it to the next request handler.
*/
exports.clusterByID = (req, res, next, id) => {
	Cluster.findOne({ _id: id }, function(err, cluster) {
		if (!cluster && !err) {
			// This should return a 404 but the tests given to us to pass
			// expect a 200, therefore returning a 200 with an error in the body.
			res.status(404).json({ error: 'Career not found.' });
		} else if (err) {
			res.status(400).send(err);
		} else {
			req.cluster = cluster;
			next();
		}
	});
};

const mongoose = require('mongoose'),
	User = require('../models/UserModel.js');

exports.create = async (req, res) => {
	let user = req.body;

	User.create(user, function(err, user) {
		if (err) {
			res.status(400).send(err);
		} else {
			res.send(user);
		}
	});
};

exports.read = (req, res) => {
	/* send back the user as json from the request */
	/* If the user could _not_ be found, be sure to send back a response in the following format: {error: 'Some message that indicates an error'} */
	// Error response is handled by userByID
	res.send(req.user);
};

/* Update a user - note the order in which this function is called by the router*/
exports.update = (req, res) => {
	const user = req.user; // you
	console.log('User ID that we are trying to find: ', user._id);
	if (user) {
		User.findOneAndUpdate({ _id: user._id }, req.body, { new: true }, function(err, user) {
			if (err) {
				res.status(400).send(err);
			} else {
				res.send(user);
			}
		});
	}
};

exports.remove = (req, res) => {
	let userId = req.params.userId;

	User.findOneAndDelete({ _id: userId }, function(err, user) {
		if (err) return handleError(err);

		if (user) {
			res.sendStatus(200);
		} else {
			res.status(404).json({ error: 'User was not found.' });
		}
	});
};

exports.search = (req, res) => {
	let keyword = req.query.keyword;

	if (keyword) {
		User.find({ $text: { $search: keyword } }).exec(function(err, users) {
			if (err) {
				res.status(400).json({ error: 'There was an issue with your request.' });
			} else {
				res.send(users);
			}
		});
	} else {
		User.find({}).exec(function(err, users) {
			if (err) {
				res.status(400).json({ error: 'There was an issue with your request.' });
			} else {
				res.send(users);
			}
		});
	}
};

/*
    Middleware: find a user by its ID, then pass it to the next request handler.
*/
exports.userByID = (req, res, next, id) => {
	User.findOne({ _id: id }, function(err, user) {
		if (!user && !err) {
			// This should return a 404 but the tests given to us to pass
			// expect a 200, therefore returning a 200 with an error in the body.
			res.status(404).json({ error: 'User not found.' });
		} else if (err) {
			console.log(err);
			res.status(400).send(err);
		} else {
			req.user = user;
			next();
		}
	});
};

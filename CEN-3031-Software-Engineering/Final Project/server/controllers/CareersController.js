/* Dependencies */
// import mongoose from 'mongoose';
// import Career from '../models/CareerClusterModel.js';

const mongoose = require('mongoose'),
	Career = require('../models/CareerModel.js');


exports.create = async (req, res) => {
	let career = req.body;
	career.salary_ranges = {};
	career.salary_ranges.entry = career.entry_wage;
	career.salary_ranges.median = career.median_wage;
	career.salary_ranges.mean = career.mean_wage;
	career.outlook = career.growth_rate;
	career.important_subjects = career.important_subjects.split(',').map((e) => String(e).trim());
	career.keywords = career.keywords.split(',').map((e) => String(e).trim());

	Career.create(career, function(err, career) {
		if (err) {
			res.status(400).send(err);
		} else {
			res.send(career);
		}
	});
};

exports.read = (req, res) => {
	/* send back the career as json from the request */
	/* If the career could _not_ be found, be sure to send back a response in the following format: {error: 'Some message that indicates an error'} */
	// Error response is handled by careerByID
	res.send(req.career);
};

/* Update a career - note the order in which this function is called by the router*/
exports.update = (req, res) => {
	let career = req.body;
	console.log(career);
	career.salary_ranges = {};
	career.salary_ranges.entry = career.entry_wage;
	career.salary_ranges.median = career.median_wage;
	career.salary_ranges.mean = career.mean_wage;
	career.outlook = career.growth_rate;

	if (typeof career.important_subjects === 'object') {
		career.important_subjects = career.important_subjects.map((e) => String(e).trim());
	} else {
		career.important_subjects = career.important_subjects.split(',').map((e) => String(e).trim());
	}

	if (typeof career.keywords === 'object') {
		career.keywords = career.keywords.map((e) => String(e).trim());
	} else {
		career.keywords = career.keywords.split(',').map((e) => String(e).trim());
	}

	if (career) {
		Career.findOneAndUpdate({ _id: career._id }, req.body, { new: true }, function(err, career) {
			if (err) {
				res.status(400).send(err);
			} else {
				res.send(career);
			}
		});
	}
};

exports.remove = (req, res) => {
	let careerId = req.params.careerId;

	Career.findOneAndDelete({ _id: careerId }, function(err, career) {
		if (err) return handleError(err);

		if (career) {
			res.sendStatus(200);
		} else {
			// Sending a 404 with an error message if career is not found
			// debating if this should be a 404 or a 200 as the tests expect a
			// 200 whe the career is not found, but I believe 404 makes more sense
			res.status(404).json({ error: 'Career was not found.' });
		}
	});
};

exports.search = (req, res) => {
	let keyword = req.query.keyword;
	let cluster = req.query.cluster;

	if (cluster) {
		Career.find({ type: cluster }).sort('name').exec(function(err, careers) {
			if (err) {
				res.status(400).json({ error: 'There was an issue with your request.' });
			} else {
				res.send(careers);
			}
		});
	}

	if (keyword) {
		Career.find({ $text: { $search: keyword } }).sort({ code: 1 }).exec(function(err, careers) {
			if (err) {
				res.status(400).json({ error: 'There was an issue with your request.' });
			} else {
				res.send(careers);
			}
		});
	} else {
		Career.find({}).sort({ code: 1 }).exec(function(err, careers) {
			if (err) {
				res.status(400).json({ error: 'There was an issue with your request.' });
			} else {
				res.send(careers);
			}
		});
	}
};

/*
    Middleware: find a career by its ID, then pass it to the next request handler.
*/
exports.careerByID = (req, res, next, id) => {
	Career.findOne({ _id: id }, function(err, career) {
		if (!career && !err) {
			// This should return a 404 but the tests given to us to pass
			// expect a 200, therefore returning a 200 with an error in the body.
			res.status(404).json({ error: 'Career not found.' });
		} else if (err) {
			res.status(400).send(err);
		} else {
			req.career = career;
			next();
		}
	});
};

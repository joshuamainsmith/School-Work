//This file is to give the credit to the project 3 team at UF
import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import './Credit.css';

//Hook function
const Credit = () => {
	return (
		<footer className="footer footer-transparent">
		<div className="container">
			<div className="row">
				<div className="col-sm-12">
				<ul>
					<li>Florida Middle School Career's Website</li>
				</ul>
				</div>
			</div>
			<div className="row">
				<div className="col-sm-12">
				<ul>
				<li><a href="/">Career's Website Designed by the studens in the CEN3031 class at University of Florida.</a></li>
				</ul>
				</div>
			</div>
			<div className="copyright">
				Group 3 - Made with dedication
			</div>
		</div>
		</footer>
	);
}

export default Credit;

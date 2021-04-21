import React from 'react';
//import { Button } from 'reactstrap';
import './Home.css';
//import { Link } from 'react-router-dom';

//import GridContainer from "../../components/Grid/GridContainer.js";
//import GridItem from "../../components/Grid/GridItem.js";
//import Card from "../../components/Card/Card.js";
//import CardBody from "../../components/Card/CardBody.js";
//import CardHeader from "../../components/Card/CardHeader.js";
//import CardFooter from "../../components/Card/CardFooter.js";
//import Heading from "../../components/Heading/Heading.js";
import styles from "../../assets/jss/material-dashboard-pro-react/views/gridSystemStyle.js";
import { makeStyles } from "@material-ui/core/styles";

const bgImage = require('./img/bg.jpeg')
const useStyles = makeStyles(styles);

const bgStyle = {
  backgroundImage: `url(${bgImage})`,
	backgroundSize: 'cover',
	bacgroundPosition: 'center',
	width: '100vw',
	height: '100vh'
};

function Home() {
	const classes = useStyles();
	return (
		<>
		<div
		className="page-header header-filter"
		style={bgStyle}
		>
		<div className="container">
			<div className="row">
				<div className="col-md-12 text-center">
					<h1 className="title ">Career Finder</h1>
				</div>
			</div>
      <div className="row">
        <div className="col-md-12 text-center">
          <h4 className="title">We are helping students around the globe find the career of their dreams.</h4>
        </div>
      </div>
      <div className="row">
        <div className="col-md-12 text-center">
          <a
            href="/careers"
            className="btn btn-info btn-fill btn-round"
            >Search Careers</a
          >
        </div>
      </div>
		</div>
		</div>
		</>
	);
}

export default Home;

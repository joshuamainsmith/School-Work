import React, { useState, useEffect } from 'react';
import './IndexClusters.css';
import { Link, useLocation } from 'react-router-dom';
import CardBody from "../../components/Card/CardBody.js";
import GridItem from "../../components/Grid/GridItem.js";
import Card from "../../components/Card/Card.js";
import CardHeader from "../../components/Card/CardHeader.js";
// @material-ui/core components
import { makeStyles } from "@material-ui/core/styles";

import styles from "../../assets/jss/material-dashboard-pro-react/views/gridSystemStyle.js";

const useStyles = makeStyles(styles);

function useQuery() {
	return new URLSearchParams(useLocation().search);
}

function IndexClusters(props) {
	let query = useQuery();
	const [ loadedClusters, setloadedClusters ] = useState([]);
	const classes = useStyles();

	useEffect(() => {
		const fetchClusters = async () => {
			let uri;
			const cluster = query.get('cluster')
			if (cluster) {
				uri = '/api/career_clusters?cluster=' + cluster
			} else {
				uri = '/api/career_clusters/'
			}
			const response = await fetch(uri);
			const responseData = await response.json();

			setloadedClusters(responseData);
		};

		fetchClusters();
	}, []);


	const clusterList = loadedClusters.map((cluster) => {

		return (
			<GridItem xs={12} sm={12}>
				<Card product className={classes.cardHover}>
					<CardHeader className={classes.cardHeaderHover}>
						<h3><Link to={"/cluster/" + cluster._id}>{cluster.name}</Link></h3>
					</CardHeader>
					<CardBody>
						<p>{cluster.description}</p>
					</CardBody>
				</Card>
			</GridItem>
		);
	});

	return (
		<>
		<header>
			<h1 className="cluster-header">Cluster</h1>
		</header>
		<div className="container">
			{clusterList}
		</div>
		</>
	);
}

export default IndexClusters;

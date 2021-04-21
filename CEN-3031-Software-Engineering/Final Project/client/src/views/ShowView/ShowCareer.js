import React, { useState, useEffect, useContext } from 'react';
import { Button, ModalHeader, ModalBody, ModalFooter, Modal } from 'reactstrap';
import { AuthContext } from '../../Context/AuthContext'
import './ShowCareer.css';
import ReactPlayer from 'react-player';
// @material-ui/core components
import { makeStyles } from "@material-ui/core/styles";

// core components
import GridContainer from "../../components/Grid/GridContainer.js";
import GridItem from "../../components/Grid/GridItem.js";
import Card from "../../components/Card/Card.js";
import CardBody from "../../components/Card/CardBody.js";
import CardHeader from "../../components/Card/CardHeader.js";
import CardFooter from "../../components/Card/CardFooter.js";
import Heading from "../../components/Heading/Heading.js";
import CardIcon from "../../components/Card/CardIcon.js";

// @material-ui/icons
// import ContentCopy from "@material-ui/icons/ContentCopy";

import MonetizationOnIcon from '@material-ui/icons/MonetizationOn';
import InfoIcon from '@material-ui/icons/Info';
import SchoolIcon from '@material-ui/icons/School';
import ShowChartIcon from '@material-ui/icons/ShowChart';
import ListIcon from '@material-ui/icons/List';
import SupervisorAccountIcon from '@material-ui/icons/SupervisorAccount';
import SweetAlert from "react-bootstrap-sweetalert";

import styles from "../../assets/jss/material-dashboard-pro-react/views/dashboardStyle.js";
import alertStyles from "../../assets/jss/material-dashboard-pro-react/views/sweetAlertStyle.js";

const useStyles = makeStyles(styles);
const useAlertStyles = makeStyles(alertStyles);

const centerStyle = {
	marginLeft: 'auto',
	marginRight: 'auto'
}

function capitalize(str) {
	if(str) {
		return str.charAt(0).toUpperCase() + str.slice(1);
	}
	return str
}

function projectedGrowthColor(outlook) {
	if(outlook > 9) {
		return "success"
	}
	if (outlook > 2) {
		return "warning"
	}
	return "danger"
}

function CareerShow(props) {
	const {user} = useContext(AuthContext);
	const [alert, setAlert] = React.useState(null);

	const classes = useStyles();
	const alertClasses = useAlertStyles();

	const hideAlert = () => {
    setAlert(null);
  };

	const basicInfo = (name, msg) => {
    setAlert(
      <SweetAlert
        style={{ display: "block", marginTop: "-100px" }}
        title={name}
        onConfirm={() => hideAlert()}
        onCancel={() => hideAlert()}
        confirmBtnCssClass={alertClasses.button + " " + alertClasses.info}
      >
				<small>{msg}</small>
			</SweetAlert>
    );
  };

	const adminButtons = () => {
		return (
			<>
				{
					user.role === "admin" ?
					<GridItem xs={12}>
						<Card>
						<CardHeader color="danger" stats icon>
							<CardIcon color="danger">
								<SupervisorAccountIcon />
							</CardIcon>
							<p className={classes.cardCategory}>Admin View</p>
							<h3 className={classes.cardTitle}>Actions</h3>
						</CardHeader>
						<CardBody>
							<GridContainer>
								<GridItem xs={12} sm={6} md={6}>
									<Card>
										<CardBody className="textCenter">
											<a href={`/career/${props.career._id}/edit`} id="edit" name="edit">
												<Button color="warning" className="float-right btn-block" name="edit">
													Edit
												</Button>
											</a>
										</CardBody>
									</Card>
								</GridItem>
								<GridItem xs={12} sm={6} md={6}>
									<Card>
										<CardBody className="textCenter">
											<Button color="danger" className="float-right btn-block" name="delete" onClick={toggle}>
												Delete
											</Button>
											<Modal isOpen={modal} toggle={toggle} className={props.className}>
												<ModalHeader toggle={toggle}>Confirm Deletion of {props.career.name}</ModalHeader>
												<ModalBody>Are you sure you want to delete?</ModalBody>
												<ModalFooter>
													<Button color="primary" onClick={handleDelete}>
														Confirm
													</Button>{' '}
													<Button color="secondary" onClick={toggle}>
														Cancel
													</Button>
												</ModalFooter>
											</Modal>
										</CardBody>
									</Card>
								</GridItem>
							</GridContainer>
						</CardBody>
						<CardFooter stats onClick={() => basicInfo('Admin View', 'You have access to these actions because you are an Admin in this website. Please thread carefully!.')}>
							<div className={classes.stats}>
								<InfoIcon />
								More Info
							</div>
						</CardFooter>
						</Card>
					</GridItem> : null
				}
			</>
		)
	}

	const listSubjects = props.career.important_subjects.map((item) =>
		<GridItem xs={12} sm={6} md={4} key={item._id}>
			<Card>
				<CardBody>
					<a href={"https://www.khanacademy.org/search?page_search_query=" + item}><h4 className={classes.cardTitle}>{capitalize(item)}</h4></a>
				</CardBody>
			</Card>
		</GridItem>
	);

	async function handleDelete() {
		try {
			fetch(`/api/careers/${props.career._id}`, { method: 'delete' });

			props.history.push('/careers/');
		} catch (error) {
			console.error(error);
		}
	}

	const [ modal, setModal ] = useState(false);

	const toggle = () => setModal(!modal);

	return (
		<div className="container">
			{alert}
			<div className="container">
				<div className="row">
					<div className="col-sm-12 text-center">
						<a href={"https://www.indeed.com/jobs?q=" + props.career.name}><Heading title={props.career.name}/></a>
					</div>
				</div>
			</div>
			<GridContainer>
				{adminButtons()}
				<GridItem xs={12}>
					<Card>
						<CardBody style={centerStyle}>
							<ReactPlayer url = { props.career.video_link } ></ReactPlayer>
						</CardBody>
					</Card>
				</GridItem>
				<GridItem xs={12}>
					<Card product className={classes.cardCategory}>
					<CardHeader color={projectedGrowthColor(props.career.outlook)} stats icon>
						<CardIcon color={projectedGrowthColor(props.career.outlook)}>
							<ShowChartIcon />
						</CardIcon>
						<p className={classes.cardCategory}>Growth Rate</p>
						<h3 className={classes.cardTitle}>{props.career.outlook ? props.career.outlook + "%" : "N/A"}</h3>
					</CardHeader>
						<CardHeader className={classes.cardCategory}>

							<h5>{props.career.type}</h5>
							<p>{props.career.description}</p>

						</CardHeader>
					</Card>
				</GridItem>

				<GridItem xs={12} sm={12} md={6} lg={4}>
          <Card>
            <CardHeader color="info" stats icon>
              <CardIcon color="info">
                <MonetizationOnIcon />
              </CardIcon>
							<p className={classes.cardCategory}>Entry Wage</p>
              <h3 className={classes.cardTitle}>{props.career.salary_ranges.entry ? "$" + props.career.salary_ranges.entry.toLocaleString() : "N/A"}</h3>
            </CardHeader>
            <CardFooter stats onClick={() => basicInfo('Entry Wage', 'The entry wage is the typical wage that employees receive when they are first starting in a profession. It is determined by adding together all of the wages of employees with 1-2 years of experience in a specific job or industry and dividing that total by the number of employees in that category.')}>
              <div className={classes.stats}>
								<InfoIcon />
                More Info
              </div>
            </CardFooter>
          </Card>
        </GridItem>
        <GridItem xs={12} sm={12} md={6} lg={4}>
          <Card>
            <CardHeader color="info" stats icon>
              <CardIcon color="info">
                <MonetizationOnIcon />
              </CardIcon>
							<p className={classes.cardCategory}>Mean Wage</p>
              <h3 className={classes.cardTitle}>{props.career.salary_ranges.mean ? "$" + props.career.salary_ranges.mean.toLocaleString() : "N/A"}</h3>
            </CardHeader>
            <CardFooter stats onClick={() => basicInfo('Mean Wage', 'The mean wage is the average wage that employees receive for the same work performed during a given period of time. It is determined by adding together all of the wages of employees in a specific job or industry and dividing that total by the number of employees.')}>
							<div className={alertClasses.center}>
              	<div className={classes.stats}>
									<InfoIcon />
									More Info
								</div>
              </div>
            </CardFooter>
          </Card>
        </GridItem>
				<GridItem xs={12} sm={12} md={6} lg={4}>
          <Card>
            <CardHeader color="info" stats icon>
              <CardIcon color="info">
                <MonetizationOnIcon />
              </CardIcon>
							<p className={classes.cardCategory}>Median Wage</p>
              <h3 className={classes.cardTitle}>{props.career.salary_ranges.median ? "$" + props.career.salary_ranges.median.toLocaleString() : "N/A"}</h3>
            </CardHeader>
            <CardFooter stats onClick={() => basicInfo('Median Wage', 'Median wage is the limit between the amount earned by 50 percent of workers who are the lowest paid and 50 percent of workers who are the highest paid in a particular job or industry occupation.')}>
              <div className={classes.stats}>
								<InfoIcon />
                More Info
              </div>
            </CardFooter>
          </Card>
        </GridItem>


				<GridItem xs={12} sm={12} md={12} lg={12}>
          <Card>
            <CardHeader color="primary" stats icon>
              <CardIcon color="primary">
                <SchoolIcon />
              </CardIcon>
							<p className={classes.cardCategory}>Education Required</p>
              <h3 className={classes.cardTitle}>{capitalize(props.career.education)}</h3>
            </CardHeader>
						<CardBody>
							<h3>Important Subjects</h3>
							<GridContainer>
								{listSubjects}
							</GridContainer>
						</CardBody>
            <CardFooter stats onClick={() => basicInfo('Education', 'The typical minimum required education you need to go into this career. The list of subjects shows what to study to be ready for this career.')}>
              <div className={classes.stats}>
								<InfoIcon />
                More Info
              </div>
            </CardFooter>
          </Card>
        </GridItem>
			</GridContainer>
		</div>
	);
}

const ShowCareer = (props) => {
	const [ careerId, setCareerId ] = useState(props.match.params.id);
	const [ loadedCareer, setLoadedCareer ] = useState({ salary_ranges: {}, important_subjects: [], keywords: [] });

	useEffect(() => {
		const fetchCareers = async () => {
			const response = await fetch('/api/careers/' + careerId);

			const responseData = await response.json();

			setLoadedCareer(responseData);
			setCareerId(careerId);
		};

		fetchCareers();
	}, [careerId]);

	return <CareerShow career={loadedCareer} history={props.history} />;
};

export default ShowCareer;

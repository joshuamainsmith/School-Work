import React from 'react';
import './Celebs.css';
import { Card, CardImg, CardText, CardBody, CardTitle, CardSubtitle, Button, CardGroup, Container, CardFooter } from 'reactstrap';

import Angela from '../../assets/angela_bassett.jpg';
import Gerard from '../../assets/gerard_butler.jpg';
import Myron from '../../assets/myron_rolle.jpg';
import Ken from '../../assets/ken_jeong.jpg';
import John from '../../assets/John_Urschel.jpg';
import Mayim from '../../assets/Mayim_Bialik.jpg'
import Tom from '../../assets/Tom_Scholz.jpg';
import David from '../../assets/David_Duchovny.JPG';
import Steve from '../../assets/Steve_Young.jpg';

const CelebsView = () => {
	return (
		<>
		<header>
			<h1 className="celebs-header">Famous Celebrities</h1>
		</header>
		<Container>
			<CardGroup>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={Angela} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>Angela Bassett</h3></CardTitle>
						<CardSubtitle>Master of Fine Arts from Yale School of Drama</CardSubtitle>
						<CardText>
							Angela has been in several movies along with winning several awards.  Just to name one, Screen Actor Guild Award for Outstanding Performance by a cast in a Motion Picture - 2019 Black Panther.
						</CardText>
					</CardBody>
					<CardFooter>
						<Button block color="primary" href="/careers?keyword=fine+arts">Relevant Careers</Button>
					</CardFooter>
				</Card>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={Gerard} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>Gerard Butler</h3></CardTitle>
						<CardSubtitle>Law Degree from the University of Glasgow School of Law</CardSubtitle>
						<CardText>
							The Scottish-born actor-best known for his movies which include 300, Law Abiding Citizen, Den of Thieves and most recently Angel has Fallen.
						</CardText>
					</CardBody>
					<CardFooter>
						<Button block color="primary" href="/careers?keyword=law">Relevant Careers</Button>
					</CardFooter>
				</Card>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={John} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>John Cameron Urschel</h3></CardTitle>
						<CardSubtitle>Masters in Mathematics</CardSubtitle>
						<CardText>
							John retired from the Baltimore Ravens in 2017.  He was drafted in the fifth round of the 2014 NFL Draft from Penn State where he earned a Master's degree in Mathematics.  He is now persuing a Ph.D. in Mathematics from M.I.T.
						</CardText>
					</CardBody>
					<CardFooter>
						<Button block color="primary" href="/careers?keyword=math">Relevant Careers</Button>
					</CardFooter>
				</Card>
				</CardGroup>
				<CardGroup>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={Ken} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>Kendrick Kang-Joh Jeong</h3></CardTitle>
						<CardSubtitle>Licensed Physician</CardSubtitle>
						<CardText>
							Ken is moost notable for his role in the Hangover series.  He is a licensed physician.  However, he has since stopped practicing in favor of his acting career.
						</CardText>
					</CardBody>
					<CardFooter>
						<Button block color="primary" href="/careers?keyword=medical">Relevant Careers</Button>
					</CardFooter>
				</Card>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={Myron} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>Myron Rolle</h3></CardTitle>
						<CardSubtitle>MSc in Medical Anthropology</CardSubtitle>
						<CardText>
							Myron was a sixth roound draft selection of the Tennessee Titans in 2010.  He retired from football tp persue a medical degree.  He graduated from Florida State univeristy College of Medicine.  He was also a Rhodes Scholarship winner and a student at St. Edmund Hall, Oxford University during the 2009-2010 academic year.  He wants to be a neurosurgeon.
						</CardText>
					</CardBody>
					<CardFooter>
						<Button block color="primary" href="/careers?keyword=science">Relevant Careers</Button>
					</CardFooter>
				</Card>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={Mayim} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>Mayim Bialik</h3></CardTitle>
						<CardSubtitle>Ph.D. in Neuroscience</CardSubtitle>
						<CardText>
							Mayim is most notable for her roles in Blossom (1991-1995) and most recently in The Big Bang Theory as Dr. Amy Farah Fowler.  She earned her Ph.D. froom UCLA in neuroscience.
						</CardText>
					</CardBody>
					<CardFooter>
						<Button block color="primary" href="/careers?keyword=neuroscience">Relevant Careers</Button>
					</CardFooter>
				</Card>
				</CardGroup>
				<CardGroup>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={Tom} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>Tom Scholz</h3></CardTitle>
						<CardSubtitle>Master's Degree in Mechanical Engineering from MIT</CardSubtitle>
						<CardText>
							Tom was born in Toledo, Ohio.  He went on to get a Bachelor's and Master's degree in Mechanical Engineering from Massachusetts of Technology.  He is moost notable for being in the band Boston.  He went on to start a company under the Rockman brand.
						</CardText>
					</CardBody>
					<CardFooter><Button block color="primary" href="/careers?keyword=engineering">Relevant Careers</Button></CardFooter>
				</Card>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={David} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>David Duchovny</h3></CardTitle>
						<CardSubtitle>Master's in English Literature from Yale University</CardSubtitle>
						<CardText>
							David is most notable for his roles as FBI Agent Fox Mulder on The X-Files and as a writer on Californication.  Both roles earned him a Golden Globe Award.  He earned his under graduate degree in English Literature from Princeton University.
						</CardText>
					</CardBody>
					<CardFooter><Button block color="primary" href="/careers?keyword=english">Relevant Careers</Button></CardFooter>
				</Card>
				<Card>
					<div className="card-container">
						<CardImg className="celeb" top width="100%" src={Steve} alt="Card image cap" />
					</div>
					<CardBody>
						<CardTitle><h3>Steve Young</h3></CardTitle>
						<CardSubtitle>Law Degree</CardSubtitle>
						<CardText>
							Steve Young played college football at Brigham Young University where he also earned a Law degree in 1994.  After signed a $40 million deal in 1984 for the USFL, he then went on to play for Tampa Bay and San Fransisco where he won a Super Bowl in 1995.
						</CardText>
					</CardBody>
					<CardFooter><Button block color="primary" href="/careers?keyword=law">Relevant Careers</Button></CardFooter>
				</Card>
			</CardGroup>
		</Container>
		</>
	);
};

export default CelebsView;

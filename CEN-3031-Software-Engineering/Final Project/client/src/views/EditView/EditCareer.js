import React, { useState, useEffect } from 'react';
import { Form, Row, Col, FormGroup, Button, Label, Input } from 'reactstrap';

const EditCareer = (props) => {
	const initialState = {
		name: '',
		type: '',
		description: '',
		keywords: '',
		important_subjects: '',
		entry_wage: '',
		median_wage: '',
		mean_wage: '',
		growth_rate: '',
		education: '',
		video_link: ''
	};
	const [ career, setCareer ] = useState(initialState);

	function handleChange(event) {
		setCareer({ ...career, [event.target.name]: event.target.value });
	}

	function handleSubmit(event) {
		
		event.preventDefault();
		async function postCareer() {
			fetch('/api/careers/' + career._id, {
				method: 'put',
				body: JSON.stringify(career),
				headers: {
					Accept: 'application/json',
					'Content-Type': 'application/json'
				}
			})
				.then((response) => response.json())
				.then((data) => {
					props.history.push('/career/' + data._id);
				})
				.catch((error) => {
					console.log('Error: ', error);
				});
		}
		postCareer();
	}
	const [ careerId, setCareerId ] = useState(props.match.params.id);

	const [ clusters, setClusters ] = useState([]);

	useEffect(() => {
		const fetchCareers = async () => {
			const response = await fetch('/api/careers/' + careerId);

			const responseData = await response.json();
			responseData['mean_wage'] = responseData.salary_ranges.mean;
			responseData['median_wage'] = responseData.salary_ranges.median;
			responseData['entry_wage'] = responseData.salary_ranges.entry;
			responseData['growth_rate'] = responseData.outlook;
			setCareer(responseData);
			setCareerId(careerId);
		};

		const fetchClusters = async () => {
			const responseCluster = await fetch('/api/career_clusters/');
			const responseDataCluster = await responseCluster.json();
			setClusters(responseDataCluster);
			
		}

		fetchCareers();
		fetchClusters();
	}, [careerId]);

	return (
		<div className="form-wrapper">
			<Form id="career-create-form" className="container">
				<Row form>
					<Col md={6}>
						<FormGroup>
							<Label>Name</Label>
							<Input
								type="text"
								name="name"
								id="careerName"
								value={career.name}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
					<Col md={6}>
						<FormGroup>
							<Label>Cluster</Label>
							<Input
								type="select"
								name="type"
								id="careerType"
								
								onChange={handleChange}
							>
								{clusters.map(cluster => {
									return (
										<option selected={cluster.name === career.type} value={cluster.name}> {cluster.name} </option>
									)
								})}
								
							</Input>
						</FormGroup>
					</Col>
				</Row>

				<Row form>
					<Col md={12}>
						<FormGroup>
							<Label>Career Description</Label>
							<small id="descriptionHelp" className="form-text text-muted">
								A brief description of the career.
							</small>
							<Input
								type="textarea"
								name="description"
								id="careerDescription"
								value={career.description}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
				</Row>

				<Row form>
					<Col md={12}>
						<FormGroup>
							<Label>Career Keywords</Label>
							<small id="keywordsHelp" class="form-text text-muted">
								A list of comma separated values.
							</small>
							<Input
								type="textarea"
								name="keywords"
								id="careerKeywords"
								value={career.keywords}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
				</Row>

				<Row form>
					<Col md={12}>
						<FormGroup>
							<Label for="importantSubjects">Important Subjects</Label>
							<small id="subjectsHelp" class="form-text text-muted">
								A list of comma separated values.
							</small>
							<Input
								type="textarea"
								name="important_subjects"
								id="importantSubjects"
								value={career.important_subjects}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
				</Row>

				<Row form>
					<Col md={4}>
						<FormGroup>
							<Label>Entry Wage</Label>
							<Input
								type="text"
								name="entry_wage"
								id="entryWage"
								placeholder="$0.00"
								value={career.entry_wage}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
					<Col md={4}>
						<FormGroup>
							<Label>Mean Wage</Label>
							<Input
								type="text"
								name="mean_wage"
								id="meanWage"
								placeholder="$0.00"
								value={career.mean_wage}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
					<Col md={4}>
						<FormGroup>
							<Label>Median Wage</Label>
							<Input
								type="text"
								name="median_wage"
								id="medianWage"
								placeholder="$0.00"
								value={career.median_wage}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
				</Row>

				<Row form>
					<Col md={12}>
						<FormGroup>
							<Label>Growth Rate</Label>
							<small id="growthRateHelp" class="form-text text-muted">
								Expected growth rate in the next year.
							</small>
							<Input
								type="text"
								name="growth_rate"
								id="growthRate"
								placeholder="0.0%"
								value={career.growth_rate}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
				</Row>

				<Row form>
					<FormGroup tag="fieldset">
						<Label>Education</Label>
						<small id="descriptionHelp" className="form-text text-muted">
							Lowest education needed for career.
						</small>
						<FormGroup check>
							<Label check>
								<Input
									type="radio"
									name="education"
									onChange={handleChange}
									checked={career.education === 'none'}
								/>
								None
							</Label>
						</FormGroup>
						<FormGroup check>
							<Label check>
								<Input
									type="radio"
									name="education"
									value="high school"
									onChange={handleChange}
									checked={career.education === 'high school'}
								/>
								High School
							</Label>
						</FormGroup>
												<FormGroup check>
							<Label check>
								<Input
									type="radio"
									name="education"
									value="associates"
									onChange={handleChange}
									checked={career.education === 'associates'}
								/>
								Associate's degree
							</Label>
						</FormGroup>

						<FormGroup check>
							<Label check>
								<Input
									type="radio"
									name="education"
									value="bachelors"
									onChange={handleChange}
									checked={career.education === 'bachelors'}
								/>
								Bachelor's degree
							</Label>
						</FormGroup>
						<FormGroup check>
							<Label check>
								<Input
									type="radio"
									name="education"
									value="masters"
									onChange={handleChange}
									checked={career.education === 'masters'}
								/>
								Master's
							</Label>
						</FormGroup>
						<FormGroup check>
							<Label check>
								<Input
									type="radio"
									name="education"
									value="doctorate"
									onChange={handleChange}
									checked={career.education === 'doctorate'}
								/>
								Doctorate
							</Label>
						</FormGroup>
					</FormGroup>
				</Row>

				<Row form>
						<Col md={10}>
						<FormGroup>
							<Label>Video Link</Label>
							<Input
								type="text"
								name="video_link"
								id="videoLink"
								placeholder="https://www.example.com/xyxyxy"
								value={career.video_link}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>

</Row>

				<Row form>
					<Col md={12}>
						<Button href="/careers" color="primary" className="float-right" onClick={handleSubmit}>
							Save
						</Button>

						<a href="/careers" id="cancel" name="cancel" className="btn btn-secondary float-left">
							Cancel
						</a>
					</Col>
				</Row>
			</Form>
		</div>
	);
};

export default EditCareer;

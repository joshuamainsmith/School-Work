import React, { useState, useEffect } from 'react';
import { Form, Row, Col, FormGroup, Button, Label, Input } from 'reactstrap';

const EditCluster = props => {

    const initialState = {
		name: '',
		description: ''
	};
	const [ cluster, setCluster ] = useState(initialState);

	function handleChange(event) {
		setCluster({ ...cluster, [event.target.name]: event.target.value });
	}

	function handleSubmit(event) {
		event.preventDefault();
		async function postCluster() {
			fetch('/api/career_clusters/' + cluster._id, {
				method: 'put',
				body: JSON.stringify(cluster),
				headers: {
					Accept: 'application/json',
					'Content-Type': 'application/json'
				}
			})
				.then((response) => response.json())
				.then((data) => {
					props.history.push('/cluster/' + data._id);
				})
				.catch((error) => {
					console.log('Error: ', error);
				});
		}
		postCluster();
	}
	const [ clusterId, setClusterId ] = useState(props.match.params.id);

	useEffect(() => {
		const fetchClusters = async () => {
			const response = await fetch('/api/career_clusters/' + clusterId);

			const responseData = await response.json();
			setCluster(responseData);
			setClusterId(clusterId);
		};

		fetchClusters();
  }, [clusterId]);

    return(
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
								value={cluster.name}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
				</Row>

				<Row form>
					<Col md={12}>
						<FormGroup>
							<Label>Career Description</Label>
							<small id="descriptionHelp" className="form-text text-muted">
								A brief description of the cluster.
							</small>
							<Input
								type="textarea"
								name="description"
								id="careerDescription"
								value={cluster.description}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
				</Row>

                <Row form>
					<Col md={12}>
						<Button href="/clusters" color="primary" className="float-right" onClick={handleSubmit}>
							Save
						</Button>

						<a href="/clusters" id="cancel" name="cancel" className="btn btn-secondary float-left">
							Cancel
						</a>
					</Col>
				</Row>
             </Form>

        </div>
    );
};
export default EditCluster;

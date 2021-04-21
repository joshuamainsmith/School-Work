import React, { useState } from 'react';
import { Form, FormGroup, Label, Input, Button } from 'reactstrap';

const CreateCluster = props => {
    const initialClusterState = {
        name: '',
        description:''
    };

    const [ careerCluster, setCareerCluster ] = useState(initialClusterState);

    function handleChange(event) {
        setCareerCluster({...careerCluster, [event.target.name]: event.target.value});
    }

    function handleSubmit(event) {
		
		event.preventDefault();
		async function postCareerCluster() {
			fetch('/api/career_clusters', {
				method: 'post',
				body: JSON.stringify(careerCluster),
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
		postCareerCluster();
	}


	return (
		<Form onSubmit={handleSubmit}>
			<FormGroup>
				<Label for="careerCluster">Career Cluster</Label>
				<Input type="text" name="name" placeholder="Enter Career Cluster" 
                value={careerCluster.name} onChange={handleChange} />
			</FormGroup>
			<FormGroup>
				<Label for="exampleText">Description</Label>
				<Input type="textArea" name="description" id="careerClusterDescription" 
                placeholder="Enter the description of the career"
                value={careerCluster.description} onChange={handleChange}/>
			</FormGroup>
			<Button color="primary" >Submit</Button>
		</Form>
	);
};

export default CreateCluster;

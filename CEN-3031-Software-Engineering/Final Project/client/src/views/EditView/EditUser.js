import React, { useState, useEffect } from 'react';
import { Row, Col, Label, Container, Button, Form, FormGroup, Input } from 'reactstrap';
//import { Link } from 'react-router-dom';

const EditUser = (props) => {
	const initialState = {
		username: '',
		role: '',
		_id: null
	};

	const [ user, setUser ] = useState(props.location.state.user);

	function handleChange(event) {
		setUser({ ...user, [event.target.name]: event.target.value });
	}

	async function handleSubmit(event) {
		
		event.preventDefault();
		try {
			const response = await fetch('/api/users/' + user._id, {
				method: 'put',
				body: JSON.stringify(user),
				headers: {
					Accept: 'application/json',
					'Content-Type': 'application/json'
				}
			});
			//const data = await response.json();
			props.history.push('/users');
		} catch (error) {
			console.log('Error: ', error);
		}
	}

	const [ userId, setUserId ] = useState(props.match.params.id);

	return (
		<Container>
			<Row>
				<Col md={6} xs="auto">
					<Label>
						<h3>Username</h3>
					</Label>
				</Col>
				<Col md={6} xs="auto">
					<Label>
						<h3>Role</h3>
					</Label>
				</Col>
			</Row>
			<hr />
			<Form id="user-create-form" className="container" onSubmit={handleSubmit}>
				<Row form>
					<Col md={6}>
						<FormGroup>
							<Input
								type="text"
								name="username"
								id="userName"
								value={user.username}
								onChange={handleChange}
							/>
						</FormGroup>
					</Col>
					<Col md={6}>
						<FormGroup>
							<Input type="select" name="role" id="userRole" value={user.role} onChange={handleChange}>
								<option>user</option>
								<option>admin</option>
							</Input>
						</FormGroup>
					</Col>
				</Row>
				<Row form>
					<Col md={12}>
						<Button color="primary" className="float-right" type="submit">
							Save
						</Button>

						<a href="/users" id="cancel" name="cancel" className="btn btn-secondary float-left">
							Cancel
						</a>
					</Col>
				</Row>
			</Form>
		</Container>
	);
};

export default EditUser;

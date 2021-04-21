import React from 'react';
import { Button, Form, FormGroup, Label, Input } from 'reactstrap';

const CreateUser = () => {
	return (
		<Form>
			<FormGroup>
				<Label for="exampleEmail">Email</Label>
				<Input type="email" name="email" id="exampleEmail" placeholder="Enter Email" />
			</FormGroup>
			<FormGroup>
				<Label for="examplePassword">Password</Label>
				<Input type="password" name="password" id="examplePassword" placeholder="Enter Password" />
			</FormGroup>
			<FormGroup>
				<Label for="exampleSelect">Select Role</Label>
				<Input type="select" name="select" id="exampleSelect">
					<option>user</option>
					<option>admin</option>
				</Input>
			</FormGroup>
			<FormGroup>
				<Label for="exampleText">About</Label>
				<Input type="textarea" name="text" id="exampleText" />
			</FormGroup>
			<Button color="primary">Submit</Button>
		</Form>
	);
};

export default CreateUser;

import React from 'react';
import { Label, Input, Button } from 'reactstrap';

const Recovery = () => {
	return (
		<div
			style={{
				position: 'absolute',
				left: '50%',
				top: '50%',
				transform: 'translate(-50%, -50%)'
			}}
		>
			<h3>Account Recovery</h3>
			<Label>Email</Label>
			<Input placeholder="Enter Email address" />
			<br />
			<div>
				<Button color="primary">Submit</Button>
			</div>
		</div>
	);
};

export default Recovery;

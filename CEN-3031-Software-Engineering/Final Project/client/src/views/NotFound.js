import React from 'react';

const bgStyle = {
  display: 'block',
	marginLeft: 'auto',
	marginRight: 'auto',
	width: 'auto',
	maxHeight: '500px',
	marginTop: '250px'
};

const NotFound = () => {
	return (
		<div className="cotainer">
			<div className="row">
				<div className="col-md-12">
				<img src="../../404-error-not-found.png" className="img-fluid" style={bgStyle} alt="Responsive" />
				</div>
			</div>
		</div>
	);
};

export default NotFound;

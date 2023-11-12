pipeline {

agent any 

tools {

nodejs "node"
sonarqubeScanner "sonar"

}


stages {


stage('Installation'){
		
	steps {
		sh 'echo "Starting Installation...."'
		sh 'npm install'	
	}

}

stage('Testing'){

	steps{

		sh 'echo "Mock testing..."'
	}


}

}












}

pipeline {

	agent any 

		tools {

			nodejs "node"

		}

	environment {
		DOCKER_CRED = credentials('docker')
			API_KEY = credentials('api-key')
			TAG = sh(script: 'date +%s', returnStdout: true).trim()
			IMAGE = "inderharrysingh/ultimate:$TAG"
			SONAR_DIR = tool "sonar"
		
	}


	stages {


		stage('Installing'){

			steps {
				sh 'echo "Starting Installation...."'
					sh 'npm install'	
			}

		}

		stage('Testing'){

			steps{

				sh '''
					$SONAR_DIR/bin/sonar-scanner \
					-Dsonar.projectKey=Netflix \
					-Dsonar.sources=. \
					-Dsonar.host.url=http://35.174.213.156:9000 \
					-Dsonar.token=sqp_7fd21cae9749745f30c227e087b7a37c27b1afa9

					'''
			}

		}


		stage('Waiting For The Scan to Conplete'){


			steps{

				                waitForQualityGate abortPipeline: false , credentialsId: 'sonarqube-token'

			}

		}


		stage('Testing Filesystem'){

			steps {

				sh 'trivy fs . '

			}

		}


		stage('Building Docker Image'){


			steps {


				sh 	"docker build . -t $IMAGE --build-arg=TMDB_V3_API_KEY=$API_KEY"

			}

		}


		stage('Testing Built Image'){

			steps {

				sh "trivy image $IMAGE"
			}
		}



		stage('Pushing Created Image'){

			steps{


				sh "docker login -u inderharrysingh -p $DOCKER_CRED"


					sh "docker push $IMAGE"


			}

		}



	}



}

pipeline {

	agent any 

		tools {

			nodejs "node"

		}

	environment {
		DOCKER_CRED = credentials('docker-credentials')
			API_KEY = credentials('api-key')
			TAG = sh(script: 'date +%s', returnStdout: true).trim()
			IMAGE = "inderharrysingh/ultimate:$TAG"

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

				sh 'echo "Mock testing..."'
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

				script {

					withCredentials([string(credentialsId: DOCKER_CRED , variable: 'DOCKER_HUB_PASSWORD')]) {
						sh "docker login -u inderharrysingh -p $DOCKER_HUB_PASSWORD"


							sh "docker push $IMAGE"
					}


				}

			}

		}



	}



}

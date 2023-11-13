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

				script {

						withSonarQubeEnv('sonar'){
									sh '''
										$SONAR_DIR/bin/sonar-scanner \
										-Dsonar.projectKey=Netflix \
										-Dsonar.sources=. \
										
									'''

						}

						}

			}

		}


		stage('Waiting For The Scan to Conplete'){


			steps{
				script {
                   			 waitForQualityGate abortPipeline: false, credentialsId: 'sonarqube-token'
                		}

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
